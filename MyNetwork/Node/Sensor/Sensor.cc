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

#include <Sensor.h>
#include <string.h>
//#include <ConnectionManagerAccess.h>
#include <FindModule.h>
#include <MacToPhyInterface.h>
#include <BasePhyLayer.h>
#include <NodeType.h>
//#define MIXIM_INET
using namespace std;

Sensor::Sensor()
{
    //position = new Coord();
    NodeType* thisType = new NodeType("SensorNode");
    this->setComponentType(thisType);
}

Sensor::~Sensor()
{
    //delete position;
}

Coord Sensor::getPosition()
{
    Coord* back;
    //getPosition();
    BasePhyLayer* phy = FindModule<BasePhyLayer*>::findSubModule(this);
    ChannelMobilityPtrType pMobType = phy->getMobilityModule();
    if(pMobType != NULL){
        back = new Coord(pMobType->getCurrentPosition());
    }
    return *back;
}

void Sensor::initialize(int stage)
{


    //4 7 10 11
    //17 - displaystring
    //cClassDescriptor* thisDescr = cClassDescriptor::getDescriptorFor(this);
    //int count = thisDescr->getFieldCount(this);
    /*
    for ( int i = 0; i < count; i++) {
        std::stringstream s;
        s << i <<" " << thisDescr->getFieldName(this, i) << " " << thisDescr->getFieldAsString(this, i, 0);
        //s << i << " " << thisDescr->getFieldName(this, i);
        cMessage *mseg = new cMessage(s.str().c_str());
        send(mseg, "worldDataGate$o");
    }*/

    /*
    std::string type = par("type");
    std::string request = "GET ";
    request += type;*/



}

void Sensor::handleMessage(cMessage *msg)
{
    delete msg;

    /*
    bubble("Sensor red data");
    string message;
    message = msg->getName();
    EV << "received:" << msg->info() << "with message" << message << endl;
    send(msg, "worldDataGate$o");*/
}

/**
 * reads the data the sensor returns at the current position
 *
 * @return integer
 */
int Sensor::getSensorData()
{
    return 0;
}

/**
 * update the position data inside the sensor by a given Coord object
 */
void Sensor::updatePosition(Coord* position)
{
    this->position = position;
}
