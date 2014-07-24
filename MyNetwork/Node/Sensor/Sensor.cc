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
using namespace std;

Sensor::Sensor()
{
    //position = new Coord();
}

Sensor::~Sensor()
{
    //delete position;
}

void Sensor::initialize(int stage)
{
    EV << "(and Sensor)" << endl;
}

void Sensor::handleMessage(cMessage *msg)
{
    bubble("Sensor red data");
    //string message;
    //message = msg->getName();
    //EV << "received:" << msg->info() << endl;
    //send(msg, "worldDataGate$o");
    delete msg;
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

Coord* Sensor::getCurrentPosition()
{
    return this->position;
}
