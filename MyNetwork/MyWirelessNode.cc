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

/**
 * returns the position of the node
 *
 * @return Coords
 */
Coord MyWirelessNode::getPosition()
{
    Coord pos = this->getCurrentPosition();
    return pos;
    //Coords *coords = new Coords();
    //TODO get the position of the node
    //coords->posX = 0;
    //coords->posY = 0;
    //return *coords;
}

void MyWirelessNode::initialize(int stage)
{
    EV << "initialize";
    LinearMobility::initialize(stage);
}

void MyWirelessNode::moveAndUpdate()
{
    EV << "moveAndUpdate";
    MovingMobilityBase::moveAndUpdate();
}
