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


Define_Module(MyWirelessNode);
Register_Class(MyWirelessNode);

//scheduleAt

MyWirelessNode::MyWirelessNode()
{
    SensorModule = new Sensor;
    //cModuleType type = new cModuleType("MyWirelessNode");
    //cComponentType = type;
}

MyWirelessNode::~MyWirelessNode()
{
    delete SensorModule;
}

int MyWirelessNode::readSensor()
{
    int data = SensorModule->getSensorData();
    return data;
}
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
 * initialize the node
 */
void MyWirelessNode::initialize(int stage)
{
    Coord back = getPosition();
    std::stringstream s;
    s << back.x << " " << back.y << " " << back.z;
    cMessage *newmsg = new cMessage(s.str().c_str());
    send(newmsg, "auchtestigate$o");
}

/**
 * proceed an incoming message
 */
void MyWirelessNode::handleMessage(cMessage *msg)
{
    EV << "-----------------------> handleMessage MyWirelessNode" << endl;
    //cMessage *newmsg = new cMessage(SIMTIME_STR(simTime()));
    //send(newmsg, "worldGate$o");
    //worldGate
}

/**
 * is called after the simulation terminated successfully
 */
void MyWirelessNode::finish()
{
    EV << "-----------------------> finish MyWirelessNode" << endl;
}
