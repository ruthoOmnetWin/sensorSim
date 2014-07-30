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
#include <NodeType.h>
using namespace std;

Sensor::Sensor()
{
    NodeType* thisType = new NodeType("SensorNode");
    this->setComponentType(thisType);
}

Sensor::~Sensor()
{
}

void Sensor::initialize(int stage)
{
    std::string type = "type";
    std::string request = "GET ";
    request += type;
    //this->updatePosition();
    cMessage *newmsg = new cMessage(request.c_str());
    //newmsg->getParList().add(position);
    send(newmsg, "toNode$o");
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
