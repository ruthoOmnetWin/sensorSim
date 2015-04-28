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

#include <AbstractProcessor.h>
#include "AbstractSensorNode.h"

AbstractProcessor::AbstractProcessor() {
    sensingIntervall = 0;
    selfMessageMeasure = NULL;
    selfMessageShiftMode = NULL;
    activatedMode = 0;

    hasTemperatureSensor = false;
    hasHumiditySensor = false;
    hasPressureSensor = false;
    hasLightSensor = false;
}

AbstractProcessor::~AbstractProcessor() {
    sensingIntervall = 0;
    selfMessageMeasure = NULL;
    selfMessageShiftMode = NULL;
    activatedMode = 0;

    hasTemperatureSensor = false;
    hasHumiditySensor = false;
    hasPressureSensor = false;
    hasLightSensor = false;
}

/**
 * initialize the relevant parameters and settings of the processor
 */
void AbstractProcessor::initialize(int stage)
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

        switchProcessorMode();
        // <- register with the battery

        //set values for schedulePeriodicSelfMessage()
        sensingIntervall = getParentModule()->par("sensingIntervall").longValue();
        shiftProcessorModeIntervall = getParentModule()->par("shiftProcessorModeIntervall").longValue();
        collectStatisticsIntervall = getParentModule()->par("collectStatisticsIntervall").longValue();

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

        AbstractSensorNode* node = (AbstractSensorNode*) getParentModule();
        if (node->par("numSensors").longValue()) {
            schedulePeriodicSelfMessage(sensing);
        } else {
            sensingIntervall = 0;
        }
        schedulePeriodicSelfMessage(shiftProcessorMode);
        schedulePeriodicSelfMessage(collectStatistics);
    }
}

/**
 * proceed incoming messages
 */
void AbstractProcessor::handleMessage(cMessage *msg)
{
    draw();
    std::string name = msg->getName();
    if (msg->isSelfMessage()) {
        if (name == "startSensingUnit") {
            schedulePeriodicSelfMessage(msg, sensing);
            startSensingUnit();
        }
        if (name == "shiftMode") {
            schedulePeriodicSelfMessage(msg, shiftProcessorMode);
            activatedMode++;
            switchProcessorMode();
        }
        if (name == "collectStatistics") {
            schedulePeriodicSelfMessage(msg, collectStatistics);
            doCollectStatistics();
        }
    } else {
        if (
            name == "Temperature" ||
            name == "Pressure" ||
            name == "Humidity" ||
            name == "Light"
        ) {
            send(msg, "connectToMemory$o");
        }
        EV << "Got Message: " << msg->getName() << endl;
    }
}

/**
 * initiate event for sensing or switching Processor mode
 */
void AbstractProcessor::schedulePeriodicSelfMessage(cMessage *msg, int intervallType)
{
    if (intervallType == sensing && sensingIntervall) {
        simtime_t scheduleTime = simTime() + sensingIntervall;
        scheduleAt(scheduleTime , msg);
    }
    if (intervallType == shiftProcessorMode && shiftProcessorModeIntervall) {
        simtime_t scheduleTime = simTime() + shiftProcessorModeIntervall;
        scheduleAt(scheduleTime , msg);
    }
    if (intervallType == collectStatistics && collectStatisticsIntervall) {
        simtime_t scheduleTime = simTime() + collectStatisticsIntervall;
        scheduleAt(scheduleTime , msg);
    }
}

/**
 * initiate event for sensing or switching Processor mode
 */
void AbstractProcessor::schedulePeriodicSelfMessage(int intervallType)
{
    if (intervallType == sensing && sensingIntervall) {
        selfMessageMeasure = new cMessage("startSensingUnit");
        simtime_t scheduleTime = simTime() + sensingIntervall;
        scheduleAt(scheduleTime , selfMessageMeasure);
    }
    if (intervallType == shiftProcessorMode && shiftProcessorModeIntervall) {
        selfMessageShiftMode = new cMessage("shiftMode");
        simtime_t scheduleTime = simTime() + shiftProcessorModeIntervall;
        scheduleAt(scheduleTime , selfMessageShiftMode);
    }
    if (intervallType == collectStatistics && collectStatisticsIntervall) {
        selfMessageStatistics = new cMessage("collectStatistics");
        simtime_t scheduleTime = simTime() + collectStatisticsIntervall;
        scheduleAt(scheduleTime , selfMessageStatistics);
    }
}

/**
 * send signal to start sensing
 */
void AbstractProcessor::startSensingUnit()
{
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
void AbstractProcessor::draw()
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
void AbstractProcessor::doCollectStatistics()
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
void AbstractProcessor::switchProcessorMode(MODES mode)
{
    //switch batteries power accounts
    if (mode == POWER_SAVING) {
        drawCurrent(currentOverTimePowerSaving, 1);
    } else if (mode == NORMAL) {
        drawCurrent(currentOverTimeNormal, 0);
    } else if (mode == HIGH_PERFORMANCE) {
        drawCurrent(currentOverTimeHighPerformance, 2);
    }
}

/**
 * switch the processor mode by a given integer
 */
void AbstractProcessor::switchProcessorMode(int mode)
{
    //switch batteries power accounts
    if (mode == 1) {
        drawCurrent(currentOverTimePowerSaving, 1);
    } else if (mode == 0) {
        drawCurrent(currentOverTimeNormal, 0);
    } else if (mode == 2) {
        drawCurrent(currentOverTimeHighPerformance, 2);
    }
}

/**
 * switches the processor to the battery mode defined by the variable
 * activatedMode
 */
void AbstractProcessor::switchProcessorMode()
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
}

/**
 * returns the processors activatedMode as enum-value MODES
 */
AbstractProcessor::MODES AbstractProcessor::getProcessorMode()
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

void AbstractProcessor::finish()
{

}

void AbstractProcessor::handleHostState(const HostState& state)
{
    AbstractBatteryAccess::handleHostState(state);
    HostState::States hostState = state.get();
    if (hostState == HostState::FAILED) {
        cancelAndDelete(selfMessageMeasure);
        cancelAndDelete(selfMessageShiftMode);
        cancelAndDelete(selfMessageStatistics);
    }
}
