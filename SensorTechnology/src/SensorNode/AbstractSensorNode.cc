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

#include <AbstractSensorNode.h>

AbstractSensorNode::AbstractSensorNode() : cModule() {
}

AbstractSensorNode::~AbstractSensorNode() {
    // TODO Auto-generated destructor stub
}

void AbstractSensorNode::initialize(int stage) {
    setNumGates();
    //generate Processor dynamically
}

void AbstractSensorNode::setNumGates() {

    int countGates = 0;
    if (par("hasTemperatureSensor")) {
        countGates++;
    }
    if (par("hasHumiditySensor")) {
        countGates++;
    }
    if (par("hasPressureSensor")) {
        countGates++;
    }
    if (par("hasLightSensor")) {
        countGates++;
    }

    cPar numGates = par("numSensors");
    numGates = countGates;
    par("numSensors") = numGates;
    EV << "Counted " << countGates << " Sensor(s) on the Node." << endl;
}
