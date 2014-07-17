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

#ifndef MYWIRELESSNODE_H_
#define MYWIRELESSNODE_H_

#include <MovingMobilityBase.h>
#include <Sensor.h>

class MyWirelessNode : public cCompoundModule
{
protected:
    Sensor sensor;
    void initialize(int stage);
    void handleMessage();
    void finish();
public:
    MyWirelessNode();
    Coord getPosition();
};

#endif /* MYWIRELESSNODE_H_ */
