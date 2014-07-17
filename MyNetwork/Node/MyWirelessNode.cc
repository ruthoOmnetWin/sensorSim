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
#include <omnetpp.h>
#include <Sensor.h>
#include <string.h>

Define_Module(MyWirelessNode);
Register_Class(MyWirelessNode);

MyWirelessNode::MyWirelessNode()
{
    SensorModule = new Sensor;
}

/**
 * returns the position of the node
 *
 * @return Coords
 */
Coord MyWirelessNode::getPosition()
{
    Coord* pos = new Coord();
    return *pos;
}

int MyWirelessNode::readSensor()
{
    int data = SensorModule->getSensorData();
    return data;
}

/**
 * initialize the node
 */
void MyWirelessNode::initialize(int stage)
{
    EV << "-----------------------> Init MyWirelessNode" << endl;
}

/**
 * proceed an incoming message
 */
void MyWirelessNode::handleMessage()
{
    EV << "-----------------------> handleMessage MyWirelessNode" << endl;
}

/**
 * is called after the simulation terminated successfully
 */
void MyWirelessNode::finish()
{
    EV << "-----------------------> finish MyWirelessNode" << endl;
}
