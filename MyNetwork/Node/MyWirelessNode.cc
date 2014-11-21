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

#include <MyWirelessNode.h>
#include <Sensor.h>
#include <string.h>
#include <NodeType.h>
#include <SimpleCoord.h>
#include <FindModule.h>
#include <MacToPhyInterface.h>
#include <BasePhyLayer.h>
#include <SimpleSensorData.h>

Define_Module(MyWirelessNode);
Register_Class(MyWirelessNode);

MyWirelessNode::MyWirelessNode()
{
    position = new Coord();
    NodeType *type = new NodeType("MyWirelessNode");
    this->componenttype = type;
    this->type = new SensorType;
    this->type->humidity = false;
    this->type->light = false;
    this->type->pressure = false;
    this->type->temperature = false;
    std::string *names = new std::string[4];
    names[0] = "humidity";
    names[1] = "pressure";
    names[2] = "temperature";
    names[3] = "light";
    this->typenames = names;
}

MyWirelessNode::~MyWirelessNode()
{
    delete this->componenttype;
    delete this->position;
    delete this->type;

    //delete this->sensorData;
}

/**
 * update the position data by a given Coord object
 */
void MyWirelessNode::updatePosition()
{
    Coord* back;
    BasePhyLayer* phy = FindModule<BasePhyLayer*>::findSubModule(this);
    ChannelMobilityPtrType pMobType = phy->getMobilityModule();
    if(pMobType != NULL){
        back = new Coord(pMobType->getCurrentPosition());
        delete position;
        position = back;
    }
}

/**
 * initialize the node
 *
 */
void MyWirelessNode::initialize(int stage)
{
    this->findSensorType();
    this->updatePosition();
    ev.bubble(this, "Initialized Position");
    numSent = 0;
    WATCH(numSent);
    numReceived = 0;
    WATCH(numReceived);
    if (ev.isGUI()) {
        updateDisplay();
    }
    this->requestData();
}

/**
 * proceed an incoming message
 */
void MyWirelessNode::handleMessage(cMessage *msg)
{
    std::string msgName = msg->getName();
    if (msg->isSelfMessage()) {
        ev.bubble(this, "Selfmessage received");
    } else if (msg->getSenderModuleId() == 16){
        EV << "MyWirelessNode: Message from Network received" << endl;
        if (msgName == "GET type") {
            this->handleGetType(msg);
        }
    } else {
        if (msgName.substr(0,4) == "POST") {

            SimpleSensorData* data = (SimpleSensorData*) msg->getParList().remove("data");

            std::string type = msgName.substr(5);
            if (type == "temperature") {
                this->temperatureData = data->sensorData;
            }else if (type == "pressure") {
                this->pressureData = data->sensorData;
            }else if (type == "light") {
                this->lightData = data->sensorData;
            } else if (type == "humidity") {
                this->humidityData = data->sensorData;
            } else {
                throw new std::exception;
            }

        } else {
            ExtendedMessage *extmsg = check_and_cast<ExtendedMessage *>(msg);
            int hopcount = extmsg->getHopCount();
            hopCountVector.record(hopcount);
            hopCountStats.collect(hopcount);
            numReceived++;
            ev.bubble(this, msg->getName());
            if (!msg->isSelfMessage()) {
                this->requestData();
            }
            if (ev.isGUI()) {
                updateDisplay();
            }
        }
    }
    delete msg;
}


void MyWirelessNode::handleGetType(cMessage* msg)
{
    /*
    EV << "MyWirelessNode: Got request for type" << endl;
    std::string name = "POST type";
    SimpleSensorType* sensorType = new SimpleSensorType("type", this->type);
    ExtendedMessage* response = this->generateMessage(name.c_str());
    response->getParList().add(sensorType);
    cGate* senderGate = msg->getSenderGate();
    std::string fullName = senderGate->getFullName();
    cGate* arrivalGate = msg->getArrivalGate();
    std::string gateName = arrivalGate->getBaseName();
    gateName += "$o";
    int gateIndex = arrivalGate->getIndex();
    sendDirect(response, senderGate);//gateName.c_str(), gateIndex
    */
}

void MyWirelessNode::requestData()
{
    updatePosition();

    //generate messages for data requests
    std::string request = "GET ";
    if (this->type->humidity) {
        this->sendDataRequest(request + this->typenames[0]);
    }
    if (this->type->pressure) {
        this->sendDataRequest(request + this->typenames[1]);
    }
    if (this->type->temperature) {
        this->sendDataRequest(request + this->typenames[2]);
    }
    if (this->type->light) {
        this->sendDataRequest(request + this->typenames[3]);
    }
}

void MyWirelessNode::sendDataRequest(std::string request)
{
    ExtendedMessage *newmsg = generateMessage(request.c_str());
    SimpleCoord *coord = new SimpleCoord("pos", this->position);
    newmsg->getParList().add(coord);
    std::stringstream s;
    s << "X: " << coord->x << " Y: " << coord->y;
    ev.bubble(this, s.str().c_str());
    send(newmsg, "toWorld$o");
    numSent++;
}

void MyWirelessNode::findSensorType()
{
    this->type->temperature = isPositive(this->findSubmodule("TemperatureSensor"));
    this->type->light = isPositive(this->findSubmodule("LightSensor"));
    this->type->pressure = isPositive(this->findSubmodule("PressureSensor"));
    this->type->humidity = isPositive(this->findSubmodule("HumiditySensor"));
}

bool MyWirelessNode::isPositive(int value) {
    if (value > 0) {
        return true;
    } else {
        return false;
    }
}

int MyWirelessNode::getSensorData()
{
    return 0;
}

ExtendedMessage* MyWirelessNode::generateMessage(const char* msgname)
{
    // Produce source and destination addresses.
    int src = getIndex();   // our module index
    int n = size();      // module vector size
    int dest = 1;//intuniform(0,n-2);

    // Create message object and set source and destination field.
    ExtendedMessage *msg = new ExtendedMessage(msgname);
    dest = msg->getArrivalGateId();
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

void MyWirelessNode::updateDisplay()
{
    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld", numReceived, numSent);
    getDisplayString().setTagArg("t",0,buf);
}

void MyWirelessNode::finish()
{
    EV << "Sent:     " << numSent << endl;
    EV << "Received: " << numReceived << endl;
    EV << "Hop count, min:    " << hopCountStats.getMin() << endl;
    EV << "Hop count, max:    " << hopCountStats.getMax() << endl;
    EV << "Hop count, mean:   " << hopCountStats.getMean() << endl;
    EV << "Hop count, stddev: " << hopCountStats.getStddev() << endl;

    recordScalar("#sent", numSent);
    recordScalar("#received", numReceived);

    hopCountStats.recordAs("hop count");
}
