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

#include <AbstractBatteryAccess.h>
#include "AbstractSensorNode.h"

AbstractBatteryAccess::AbstractBatteryAccess() {
    currentOverTime = 0.0;
    energiePerOperation = 0.0;

}

AbstractBatteryAccess::~AbstractBatteryAccess() {
    // TODO Auto-generated destructor stub
}

void AbstractBatteryAccess::initialize(int stage) {
    MiximBatteryAccess::initialize(stage);
    if (stage == 0) {
        const char * name = this->getFullName();
        std::string stringName = std::string(name);
        registerWithBattery(stringName, 1);
        EV << "Registered with Battery" << endl;
        currentOverTime = par("currentConsumption").doubleValue();
        energiePerOperation = par("energyConsumption").doubleValue();
        drawCurrent(currentOverTime, 0);
        //HostState::States state = battery->getState();
    }
}

void AbstractBatteryAccess::handleHostState(const HostState &state)
{
    HostState::States hostState = state.get();

    if (hostState == HostState::FAILED) {
        EV << "failed" << endl;
        cModule *parent = getParentModule();
        std::string name = parent->getFullName();
        if (name != "AbstractSensorNode") {
            parent = parent->getParentModule();
        }
        AbstractSensorNode* sensorNode = (AbstractSensorNode*)parent;
        sensorNode->batteryEmptied = simTime();
    } else if (hostState == HostState::BROKEN) {
        EV << "broken" << endl;
    } else if (hostState == HostState::SLEEP) {
        EV << "sleep" << endl;
    } else if (hostState == HostState::OFF) {
        EV << "off" << endl;
    }
}

void AbstractBatteryAccess::draw() {
    drawEnergy(energiePerOperation, 0);
}

void AbstractBatteryAccess::finish() {
    //EV << "Battery emptied at " << batteryEmptied.str() << endl;
}
