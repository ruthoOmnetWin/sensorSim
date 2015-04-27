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
#include <SimpleBattery.h>

AbstractSensorNode::AbstractSensorNode() : cModule() {
}

AbstractSensorNode::~AbstractSensorNode() {
    // TODO Auto-generated destructor stub
}

void AbstractSensorNode::initialize(int stage) {
    if (stage == 0) {
        //get the amount of sensors and gates needed
        setNumGates();
        //generate Processor dynamically
        createProcessor();
        //connect Memory with Processor
        connectProcessorAndMemory();
    } else if (stage == 1) {

    }
}

/**
 * counts how many sensors exist on the node
 */
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

/**
 * creates the processor module
 * depending on the different boolean parameters set inside the parameters list
 * by these parameters the sensors are created or not
 * if created, they get connected to the newly created processor gates
 */
void AbstractSensorNode::createProcessor() {
    //find the factory
    cModuleType *moduleType = cModuleType::get("sensortechnology.src.SensorNode.Processor.AbstractProcessor");

    //create module
    cModule *processor = moduleType->create("Processor", this);
    processor->finalizeParameters();

    //add gates
    //connect them to the sensors
    if (par("hasTemperatureSensor")) {
        connectProcessorAndSensor(*processor, "Temperature");
    }
    if (par("hasHumiditySensor")) {
        connectProcessorAndSensor(*processor, "Humidity");
    }
    if (par("hasPressureSensor")) {
        connectProcessorAndSensor(*processor, "Pressure");
    }
    if (par("hasLightSensor")) {
        connectProcessorAndSensor(*processor, "Light");
    }

    processor->buildInside();
}

/**
 * dynamically creates gates of the processor depending on the sensor type given (by name)
 * connects these gates to the gates of the given sensor type
 */
void AbstractSensorNode::connectProcessorAndSensor(cModule &processor, std::string SensorType) {
    //new gates
    cGate *fromSensor = processor.addGate(("from" + SensorType + "Sensor").c_str(), cGate::INPUT);
    cGate *toSensor = processor.addGate(("to" + SensorType + "Sensor").c_str(), cGate::OUTPUT);
    //find gates inside sensor
    cModule *Sensor = this->getSubmodule((SensorType + "Sensor").c_str());
    cGate *sensorOut = Sensor->gate("fromTransducerToNodeProcessor");
    cGate *sensorIn = Sensor->gate("toSensingUnitFromNodeProcessor");
    //connect
    //no need to set channels here, since they are already defined inside AnstractSensors ned file and
    //fromTransducerToNodeProcessor is just a forwarding port, so it just needs on channel
    //Transducer.toNodeProcessor --> ned.DatarateChannel {datarate=dataBandwidth;} --> fromTransducerToNodeProcessor;
    sensorOut->connectTo(fromSensor);
    toSensor->connectTo(sensorIn);
    EV << "Created connections from " << SensorType << "-sensor to the processor." << endl;
}

/**
 * connects gates of the processor with gates of the memory module
 */
void AbstractSensorNode::connectProcessorAndMemory() {
    //get memory gates
    cModule *Memory = this->getSubmodule("Memory");
    Memory->addGate("connectToProcessor", cGate::INOUT);
    cGate *inMemoryFromProcessor = Memory->gate("connectToProcessor$i");
    cGate *outMemoryToProcessor = Memory->gate("connectToProcessor$o");
    //get processor gates
    cModule *Processor =  this->getSubmodule("Processor");
    Processor->addGate("connectToMemory", cGate::INOUT);
    cGate *inProcessorFromMemory = Processor->gate("connectToMemory$i");
    cGate *outProcessorToMemory = Processor->gate("connectToMemory$o");
    //connect
    cDatarateChannel* dc = getDataChannel();
    outMemoryToProcessor->connectTo(inProcessorFromMemory, dc);
    dc->callInitialize();
    dc = getDataChannel();
    outProcessorToMemory->connectTo(inMemoryFromProcessor, dc);
    dc->callInitialize();
}

void AbstractSensorNode::handleMessage(cMessage *msg) {
    EV << "Received Message"<< endl;
}

void AbstractSensorNode::finish()
{
    //define this function
    //stop the module here
    //EV << "Finished Module" << this->getFullName() << endl;
}

/**
 * creates a new channel with the datarate defined as dataBandwidth
 */
cDatarateChannel* AbstractSensorNode::getDataChannel()
{
    cDatarateChannel* DataChannel = cDatarateChannel::create("DataChannel");
    DataChannel->setDatarate(par("dataBandwidth").doubleValue());
    return DataChannel;
}

/**
 * creates a new channel with the datarate defined as controlBandwidth
 */
cDatarateChannel* AbstractSensorNode::getControlChannel()
{
    cDatarateChannel* ControlChannel = cDatarateChannel::create("ControlChannel");
    ControlChannel->setDatarate(par("controlBandwidth").doubleValue());
    return ControlChannel;
}
