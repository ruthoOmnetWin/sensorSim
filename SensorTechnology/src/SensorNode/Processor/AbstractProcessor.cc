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

AbstractProcessor::AbstractProcessor() {
    sensingIntervall = 0;
    selfMessage = NULL;
}

AbstractProcessor::~AbstractProcessor() {
    // TODO Auto-generated destructor stub
}

void AbstractProcessor::initialize(int stage)
{
    if (stage == 0) {
        AbstractBatteryAccess::initialize(stage);
        sensingIntervall = getParentModule()->par("sensingIntervall").longValue();

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
        schedulePeriodicSelfMessage();
    }
}

void AbstractProcessor::handleMessage(cMessage *msg)
{
    draw();
    std::string name = msg->getName();
    if (msg->isSelfMessage()) {
        if (name == "startSensingUnit") {
            schedulePeriodicSelfMessage(msg);
            startSensingUnit();
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

void AbstractProcessor::schedulePeriodicSelfMessage(cMessage *msg)
{
    if (sensingIntervall) {
        simtime_t scheduleTime = simTime() + sensingIntervall;
        scheduleAt(scheduleTime , msg);
    }
}

void AbstractProcessor::schedulePeriodicSelfMessage()
{
    if (sensingIntervall) {
        selfMessage = new cMessage("startSensingUnit");
        simtime_t scheduleTime = simTime() + sensingIntervall;
        scheduleAt(scheduleTime , selfMessage);
    }
}

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

void AbstractProcessor::draw()
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
    AbstractBatteryAccess::draw();
}

/**
 * provides different modes (defined as enum)
 * defines one account on the battery per mode with
 * different power consumptions
 */
void AbstractProcessor::switchProcessorMode(int mode)
{

}

void AbstractProcessor::finish()
{
}

void AbstractProcessor::handleHostState(const HostState& state)
{
    AbstractBatteryAccess::handleHostState(state);
    HostState::States hostState = state.get();
    if (hostState == HostState::FAILED) {
        cancelAndDelete(selfMessage);
    }
}
