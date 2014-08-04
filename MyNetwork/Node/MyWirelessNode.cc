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

Define_Module(MyWirelessNode);
Register_Class(MyWirelessNode);

//scheduleAt

MyWirelessNode::MyWirelessNode()
{
    position = new Coord();
    //SensorModule = new Sensor;
    NodeType *type = new NodeType("MyWirelessNode");
    this->componenttype = type;
}

MyWirelessNode::~MyWirelessNode()
{
    delete componenttype;
    delete position;
    //cancelAndDelete(timeoutmsg);
}
/*
int MyWirelessNode::readSensor()
{
    int data = SensorModule->getSensorData();
    return data;
}*/
/*
Coord* getPosition(){
    Coord *back=NULL;
    ConnectionManagerAccess *const pChanAccess = dynamic_cast<ConnectionManagerAccess *const>(this->getParentModule()->getSubmodule(sNameOfNIC.c_str())->getSubmodule(sNameOfPhyLayer.c_str()));
    if(pChanAccess != NULL){
        ChannelMobilityPtrType pMobType = pChanAccess->getMobilityModule();
        if(pMobType != NULL){
            back = new Coord(pMobType->getCurrentPosition());
        }
    }
    return back;
}*/

/**
 * update the position data inside the sensor by a given Coord object
 */
void MyWirelessNode::updatePosition()
{
    Coord* back;
    //getPosition();
    BasePhyLayer* phy = FindModule<BasePhyLayer*>::findSubModule(this);
    ChannelMobilityPtrType pMobType = phy->getMobilityModule();
    if(pMobType != NULL){
        back = new Coord(pMobType->getCurrentPosition());
    }
    delete position;
    position = back;
}

/**
 * initialize the node
 */
void MyWirelessNode::initialize(int stage)
{
    /*
    Coord back = getPosition();
    std::stringstream s;
    s << back.x << " " << back.y << " " << back.z;
    cMessage *newmsg = new cMessage(s.str().c_str());
    send(newmsg, "auchtestigate$o");
    */
}

/**
 * proceed an incoming message
 */
void MyWirelessNode::handleMessage(cMessage *msg)
{
    delete msg;
    updatePosition();
    std::string type = "type";
    std::string request = "GET ";
    request += type;
    cMessage *newmsg = new cMessage(request.c_str());
    //cArray *array = new cArray("position");
    SimpleCoord *coord = new SimpleCoord("pos", position);
    //array->add(coord);
    newmsg->getParList().add(coord);
    send(newmsg, "toWorld$o");
}

/**
 * is called after the simulation terminated successfully
 */
void MyWirelessNode::finish()
{
    EV << "-----------------------> finish MyWirelessNode" << endl;
}
