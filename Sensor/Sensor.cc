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
#include <omnetpp.h>

Sensor::Sensor()
{
    // TODO Auto-generated constructor stub

}

Sensor::~Sensor()
{
    // TODO Auto-generated destructor stub
}

Define_Module(Sensor);

/**
 * reads the data the sensor returns at the current position
 *
 * @return integer
 */
Sensor::getSensorData()
{

}

/**
 * returns the location of the sensor chip in the moment
 * returns it as an array(0 => xPos, 1 => yPos)
 *
 * @return array
 */
Sensor::getLocation()
{

}
