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
    // TODO Auto-generated constructor stub

}

AbstractProcessor::~AbstractProcessor() {
    // TODO Auto-generated destructor stub
}

void AbstractProcessor::initialize(int stage)
{
    if (stage == 0) {
        AbstractBatteryAccess::initialize(stage);
        sensingIntervall = getParentModule()->par("sensingIntervall").longValue();
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
        cMessage *selfMessage = new cMessage("startSensingUnit");
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
