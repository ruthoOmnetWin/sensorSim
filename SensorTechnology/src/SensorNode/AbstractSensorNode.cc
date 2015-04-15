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
    //get the amount of sensors and gates needed
    setNumGates();
    //generate Processor dynamically
    createProcessor();
    //connect Memory with Processor
    connectProcessorAndMemory();
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

void AbstractSensorNode::createProcessor() {
    //find the factory
    cModuleType *moduleType = cModuleType::get("sensortechnology.src.SensorNode.Processor.AbstractProcessor");

    //create module
    cModule *module = moduleType->create("Processor", this);
    module->finalizeParameters();

    //add gates
    if (par("hasTemperatureSensor")) {
        module->addGate("fromTemperatureSensor", cGate::INPUT);
        module->addGate("toTemperatureSensor", cGate::OUTPUT);
    }
    if (par("hasHumiditySensor")) {
        module->addGate("fromHumiditySensor", cGate::INPUT);
        module->addGate("toHumiditySensor", cGate::OUTPUT);
    }
    if (par("hasPressureSensor")) {
        module->addGate("fromPressureSensor", cGate::INPUT);
        module->addGate("toPressureSensor", cGate::OUTPUT);
    }
    if (par("hasLightSensor")) {
        module->addGate("fromLightSensor", cGate::INPUT);
        module->addGate("toLightSensor", cGate::OUTPUT);
    }

    module->buildInside();
}

void AbstractSensorNode::connectProcessorAndMemory() {
    //get memory gates
    cModule *Memory =  this->getSubmodule("Memory");
    Memory->addGate("connectToProcessor", cGate::INOUT);
    cGate *inMemoryFromProcessor = Memory->gate("connectToProcessor$i");
    cGate *outMemoryToProcessor = Memory->gate("connectToProcessor$o");
    //get processor gates
    cModule *Processor =  this->getSubmodule("Processor");
    Processor->addGate("connectToMemory", cGate::INOUT);
    cGate *inProcessorFromMemory = Processor->gate("connectToMemory$i");
    cGate *outProcessorToMemory = Processor->gate("connectToMemory$o");
    //connect
    outMemoryToProcessor->connectTo(inProcessorFromMemory);
    outProcessorToMemory->connectTo(inMemoryFromProcessor);
}
