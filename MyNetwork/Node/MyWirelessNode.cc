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

MyWirelessNode::MyWirelessNode()
{
    position = new Coord();
    NodeType *type = new NodeType("MyWirelessNode");
    this->componenttype = type;
}

MyWirelessNode::~MyWirelessNode()
{
    delete componenttype;
    delete position;
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
 */
void MyWirelessNode::initialize(int stage)
{
    this->updatePosition();
    ev.bubble(this, "Initialized Position");
    numSent = 0;
    WATCH(numSent);
    numReceived = 0;
    WATCH(numReceived);
    if (ev.isGUI()) {
        updateDisplay();
    }
}

void MyWirelessNode::updateDisplay()
{
    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld", numReceived, numSent);
    getDisplayString().setTagArg("t",0,buf);
}

/**
 * proceed an incoming message
 */
void MyWirelessNode::handleMessage(cMessage *msg)
{
    numReceived++;
    ev.bubble(this, msg->getName());
    if (!msg->isSelfMessage()) {
        delete msg;
        updatePosition();
        std::string type = "type";
        std::string request = "GET ";
        request += type;
        cMessage *newmsg = new cMessage(request.c_str());
        SimpleCoord *coord = new SimpleCoord("pos", position);
        newmsg->getParList().add(coord);
        std::stringstream s;
        s << "X: " << coord->x << " Y: " << coord->y;
        ev.bubble(this, s.str().c_str());
        send(newmsg, "toWorld$o");
        numSent++;
    }
    if (ev.isGUI()) {
        updateDisplay();
    }
}

/**
 * is called after the simulation terminated successfully
 */
void MyWirelessNode::finish()
{

}

int MyWirelessNode::getSensorData()
{
    return 0;
}

