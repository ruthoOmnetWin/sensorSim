//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <Processor.h>
#include <FindModule.h>
#include <BasePhyLayer.h>
#include "SensorNode.h"
#include "BatteryAccess.h"
#include "Memory.h"
#include <sstream>

Processor::Processor() {
    sensingIntervall = 0;
    selfMessageMeasure = NULL;
    selfMessageShiftMode = NULL;
    selfMessageReadAndClear = NULL;
    activatedMode = 0;

    hasTemperatureSensor = false;
    hasHumiditySensor = false;
    hasPressureSensor = false;
    hasLightSensor = false;
}

Processor::~Processor() {
    sensingIntervall = 0;
    selfMessageMeasure = NULL;
    selfMessageShiftMode = NULL;
    selfMessageReadAndClear = NULL;
    activatedMode = 0;

    hasTemperatureSensor = false;
    hasHumiditySensor = false;
    hasPressureSensor = false;
    hasLightSensor = false;
}

/**
 * initialize the relevant parameters and settings of the processor
 */
void Processor::initialize(int stage)
{
    if (stage == 0) {

        MiximBatteryAccess::initialize(stage);

        // -> register with the battery
        const char * name = this->getFullName();
        std::string stringName = std::string(name);

        registerWithBattery(stringName, par("numModes").longValue());

        //get the consumption values
        currentOverTimeNormal = par("currentConsumptionNormal").doubleValue();
        energiePerOperationNormal = par("energyConsumptionNormal").doubleValue();

        currentOverTimePowerSaving = par("currentConsumptionPowerSaving").doubleValue();
        energiePerOperationPowerSaving = par("energyConsumptionPowerSaving").doubleValue();

        currentOverTimeHighPerformance = par("currentConsumptionHighPerformance").doubleValue();
        energiePerOperationHighPerformance = par("energyConsumptionHighPerformance").doubleValue();

        peripheryNormalRatio  = getParentModule()->par("normalRatio").doubleValue();
        peripheryPowerSavingRatio = getParentModule()->par("powerSavingRatio").doubleValue();
        peripheryHighPerformanceRatio = getParentModule()->par("highPerformanceRatio").doubleValue();

        activatedModeVector.setName("power mode");
        activatedModeVector.record(activatedMode);

        sensorUnitsActive.setName("Sensor Modules Status");
        sensorUnitsActive.record(0);

        switchProcessorMode();
        // <- register with the battery

        //set values for schedulePeriodicSelfMessage()
        sensingIntervall = getParentModule()->par("sensingIntervall").longValue();
        shiftProcessorModeNormalIntervall = getParentModule()->par("shiftProcessorModeNormalIntervall").longValue();
        shiftProcessorModeHighPerformanceIntervall = getParentModule()->par("shiftProcessorModeHighPerformanceIntervall").longValue();
        shiftProcessorModePowerSavingIntervall = getParentModule()->par("shiftProcessorModePowerSavingIntervall").longValue();
        collectStatisticsIntervall = getParentModule()->par("collectStatisticsIntervall").longValue();
        readAndClearStorageIntervall = getParentModule()->par("readAndClearStorageIntervall").longValue();

        //initialize statistics
        voltage = battery->getVoltage();
        voltageStats.setName("Voltage");
        voltageStats.collect(voltage);
        voltageVector.setName("Voltage");
        voltageVector.record(voltage);

        residualRelative = battery->estimateResidualRelative();
        residualRelativeStats.setName("residualRelative");
        residualRelativeStats.collect(residualRelative);
        residualRelativeVector.setName("residualRelative");
        residualRelativeVector.record(residualRelative);

        residualAbs = battery->estimateResidualAbs();
        residualAbsStats.setName("residualAbs");
        residualAbsStats.collect(residualAbs);
        residualAbsVector.setName("residualAbs");
        residualAbsVector.record(residualAbs);

    } else if (stage == 1) {

        SensorNode* node = (SensorNode*) getParentModule();
        if (node->par("numSensors").longValue()) {
            schedulePeriodicSelfMessage(sensing);
        } else {
            sensingIntervall = 0;
        }
        schedulePeriodicSelfMessage(shiftProcessorMode);
        schedulePeriodicSelfMessage(collectStatistics);
        schedulePeriodicSelfMessage(readAndClearStorage);

        setPeriphery();

        WATCH(activatedMode);
        if (ev.isGUI()) {
            updateDisplay();
        }
    }
}

void Processor::updateDisplay()
{
    char buf[40];
    if (activatedMode == NORMAL) {
        sprintf(buf, "mode: normal");
    } else if (activatedMode == POWER_SAVING) {
        sprintf(buf, "mode: power saving");
    } else if (activatedMode == HIGH_PERFORMANCE) {
        sprintf(buf, "mode: high performance");
    } else {
        return;
    }
    getParentModule()->getDisplayString().setTagArg("t",0,buf);
}

/**
 * proceed incoming messages
 *
 * communication is not allowed when the power saving mode is active (except for events)
 */
void Processor::handleMessage(cMessage *msg)
{
    std::string name = msg->getName();
    if (msg->isSelfMessage()) {
        if (name == "startSensingUnit") {
            say("Processor: scheduling startSensingUnit");
            schedulePeriodicSelfMessage(msg, sensing);
            startSensingUnit();
            sensorUnitsActive.record(1);
        } else if (name == "shiftMode") {
            say("Processor: scheduling shiftMode");
            activatedMode++;
            switchProcessorMode();
            switchPeripheryEnergyConsumption();
            schedulePeriodicSelfMessage(msg, shiftProcessorMode);
        } else if (name == "collectStatistics") {
            say("Processor: scheduling collect Statistics");
            schedulePeriodicSelfMessage(msg, collectStatistics);
            doCollectStatistics();
        } else if (name == "readAllAndClear") {
            say("Processor: scheduling readAndClearStorage");
            schedulePeriodicSelfMessage(readAndClearStorage);
            send(msg, "connectToMemory$o");
        }
    } else {
        std::stringstream ss; ss << "Processor: Got Message: " << name << endl;
        say(ss.str());
        if (
            name == "Temperature" ||
            name == "Pressure" ||
            name == "Humidity" ||
            name == "Light"
        ) {
            sensorUnitsActive.record(0);
            say("Processor: Got measure data, saving to memory.");
            send(msg, "connectToMemory$o");
        } else if (name == "storageContent") {
            const storage empty = {"", -9999, -1};
            SimpleSensorData* data;
            cArray arr = msg->getParList();
            int k = arr.size();

            storage dataArray[k];
            for (int i = 0; i < k; i++) {
                dataArray[i] = empty;
            }

            say("Processor: received data:");
            for (int i = 0; i < k; i++) {
                data = (SimpleSensorData*) msg->getParList().remove(i);
                dataArray[i].value = data->sensorData;
                dataArray[i].timeCreated = data->timestamp;
                dataArray[i].type = data->getName();

                std::stringstream ss;
                ss << "Processor: " << dataArray[i].type << ": "<< dataArray[i].value << " (t=" << dataArray[i].timeCreated << "s)";
                say(ss.str());
            }
            delete msg;
        }
    }
    draw();
}

/**
 * initiate event for sensing or switching Processor mode
 */
void Processor::schedulePeriodicSelfMessage(cMessage *msg, int intervallType)
{
    if (intervallType == sensing && sensingIntervall) {
        simtime_t scheduleTime = simTime() + sensingIntervall;
        scheduleAt(scheduleTime , selfMessageMeasure);
    } else if (intervallType == shiftProcessorMode) {
        int addedTime = 0;
        if (getProcessorMode() == NORMAL) {
            addedTime = shiftProcessorModeNormalIntervall;
        } else if (getProcessorMode() == HIGH_PERFORMANCE) {
            addedTime = shiftProcessorModeHighPerformanceIntervall;
        } else if (getProcessorMode() == POWER_SAVING) {
            addedTime = shiftProcessorModePowerSavingIntervall;
        }
        simtime_t scheduleTime = simTime() + addedTime;
        scheduleAt(scheduleTime , msg);
    } else if (intervallType == collectStatistics && collectStatisticsIntervall) {
        simtime_t scheduleTime = simTime() + collectStatisticsIntervall;
        scheduleAt(scheduleTime , msg);
    } else if (intervallType == readAndClearStorage && readAndClearStorageIntervall) {
        simtime_t scheduleTime = simTime() + readAndClearStorageIntervall;
        scheduleAt(scheduleTime , msg);
    }
}

/**
 * initiate event for sensing or switching Processor mode
 */
void Processor::schedulePeriodicSelfMessage(int intervallType)
{
    if (intervallType == sensing && sensingIntervall) {
        selfMessageMeasure = new cMessage("startSensingUnit");
        schedulePeriodicSelfMessage(selfMessageMeasure, intervallType);
    } else if (intervallType == shiftProcessorMode) {
        selfMessageShiftMode = new cMessage("shiftMode");
        schedulePeriodicSelfMessage(selfMessageShiftMode, intervallType);
    } else if (intervallType == collectStatistics && collectStatisticsIntervall) {
        selfMessageStatistics = new cMessage("collectStatistics");
        schedulePeriodicSelfMessage(selfMessageStatistics, intervallType);
    } else if (intervallType == readAndClearStorage && readAndClearStorageIntervall) {
        selfMessageReadAndClear = new cMessage("readAllAndClear");
        schedulePeriodicSelfMessage(selfMessageReadAndClear, intervallType);
    }

}

/**
 * send signal to start sensing
 */
void Processor::startSensingUnit()
{
    say("Processor: Initiating measuring");
    cModule* SensorNode = getParentModule();
    if (SensorNode->par("hasTemperatureSensor")) {
        cMessage* msg = new cMessage("startMeasuring");
        send(msg, "toTemperatureSensor");
    }
    if (SensorNode->par("hasHumiditySensor")) {
        cMessage* msg = new cMessage("startMeasuring");
        send(msg, "toHumiditySensor");
    }
    if (SensorNode->par("hasPressureSensor")) {
        cMessage* msg = new cMessage("startMeasuring");
        send(msg, "toPressureSensor");
    }
    if (SensorNode->par("hasLightSensor")) {
        cMessage* msg = new cMessage("startMeasuring");
        send(msg, "toLightSensor");
    }
}

/**
 * draws energie from the battery and saves statistic informations
 */
void Processor::draw()
{
    doCollectStatistics();
    if (activatedMode == POWER_SAVING) {
        drawEnergy(energiePerOperationPowerSaving, 1);
    } else if (activatedMode == NORMAL) {
        drawEnergy(energiePerOperationNormal, 0);
    } else if (activatedMode == HIGH_PERFORMANCE) {
        drawEnergy(energiePerOperationHighPerformance, 2);
    }
    doCollectStatistics();
}

/**
 * collect statistical informations about the battery
 */
void Processor::doCollectStatistics()
{
    voltage = battery->getVoltage();
    voltageStats.collect(voltage);
    voltageVector.record(voltage);

    residualRelative = battery->estimateResidualRelative();
    residualRelativeStats.collect(residualRelative);
    residualRelativeVector.record(residualRelative);

    residualAbs = battery->estimateResidualAbs();
    residualAbsStats.collect(residualAbs);
    residualAbsVector.record(residualAbs);
}

/**
 * switch the processors mode by giving the modes enum value
 */
void Processor::switchProcessorMode(MODES mode)
{
    //switch batteries power accounts
    if (mode == POWER_SAVING) {
        activatedMode = 1;
    } else if (mode == NORMAL) {
        activatedMode = 0;
    } else if (mode == HIGH_PERFORMANCE) {
        activatedMode = 2;
    }
    switchProcessorMode();
}

/**
 * switch the processor mode by a given integer
 */
void Processor::switchProcessorMode(int mode)
{
    activatedMode = mode;
    switchProcessorMode();
}

/**
 * switches the processor to the battery mode defined by the variable
 * activatedMode
 */
void Processor::switchProcessorMode()
{
    //switch batteries power accounts
    if (getProcessorMode() == POWER_SAVING) {
        drawCurrent(currentOverTimePowerSaving, 1);
    } else if (getProcessorMode() == NORMAL) {
        drawCurrent(currentOverTimeNormal, 0);
    } else if (getProcessorMode() == HIGH_PERFORMANCE) {
        drawCurrent(currentOverTimeHighPerformance, 2);
    } else {
        activatedMode=0;
        switchProcessorMode();
    }
    if (ev.isGUI()) {
        updateDisplay();
    }
    activatedModeVector.record(activatedMode);
    SensorNode *node = (SensorNode*) getParentModule();
    node->say("Processor: switched power mode");
}

/**
 * returns the processors activatedMode as enum-value MODES
 */
Processor::MODES Processor::getProcessorMode()
{
    if (activatedMode == NORMAL) {
        return NORMAL;
    } else if (activatedMode == HIGH_PERFORMANCE) {
        return HIGH_PERFORMANCE;
    } else if (activatedMode == POWER_SAVING) {
        return POWER_SAVING;
    }
    return OFF;
}

void Processor::switchPeripheryEnergyConsumption()
{
    for(std::vector<cModule*>::size_type i = 0; i != periphery.size(); i++) {
        BatteryAccess* module = (BatteryAccess*) periphery[i];
        double curr = 0.0;
        if (getProcessorMode() == NORMAL) {
            curr = module->currentOverTime*peripheryNormalRatio;
        } else if (getProcessorMode() == HIGH_PERFORMANCE) {
            curr = module->currentOverTime*peripheryHighPerformanceRatio;
        } else if (getProcessorMode() == POWER_SAVING) {
            curr = module->currentOverTime*peripheryPowerSavingRatio;
        }
        module->changeDrawCurrent(curr, 0);
    }
}

void Processor::finish()
{
}

void Processor::handleHostState(const HostState& state)
{
    BatteryAccess::handleHostState(state);
    HostState::States hostState = state.get();
    if (hostState == HostState::FAILED) {
        say("Battery emptied");
        cancelAndDelete(selfMessageMeasure);
        cancelAndDelete(selfMessageShiftMode);
        cancelAndDelete(selfMessageStatistics);
    }
}

void Processor::setPeriphery()
{
    cModule* sensorNode = getParentModule();
    numDevices = sensorNode->par("numDevices");
    cModule* memory = sensorNode->getSubmodule("Memory");
    periphery.push_back(memory);
    if (hasTemperatureSensor) {
        cModule* tSensor = sensorNode->getSubmodule("TemperatureSensor");
        addSensorModules(tSensor);
    }
    if (hasHumiditySensor) {
        cModule* hSensor = sensorNode->getSubmodule("HumiditySensor");
        addSensorModules(hSensor);
    }
    if (hasPressureSensor) {
        cModule* pSensor = sensorNode->getSubmodule("PressureSensor");
        addSensorModules(pSensor);
    }
    if (hasLightSensor) {
        cModule* lSensor = sensorNode->getSubmodule("LightSensor");
        addSensorModules(lSensor);
    }
    say("Collected all Modules");
}

void Processor::addSensorModules(cModule* Sensor)
{
    BatteryAccess* SensingUnit = (BatteryAccess*) Sensor->getSubmodule("SensingUnit");
    periphery.push_back(SensingUnit);
    BatteryAccess* SignalConditioner = (BatteryAccess* )Sensor->getSubmodule("SignalConditioner");
    periphery.push_back(SignalConditioner);
    BatteryAccess* SignalConverter = (BatteryAccess*) Sensor->getSubmodule("SignalConverter");
    periphery.push_back(SignalConverter);
    BatteryAccess* Transducer = (BatteryAccess*) Sensor->getSubmodule("Transducer");
    periphery.push_back(Transducer);
}
