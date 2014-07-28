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

#ifndef SENSOR_H_
#define SENSOR_H_

#include <omnetpp.h>
#include <Coord.h>
#include <CustomLinearMobility.h>

class Sensor : public CustomLinearMobility
{
protected:
    void initialize(int stage);
    void handleMessage(cMessage *msg);
    void activity(){};
    void finish(){};

protected:
    Coord* position;
public:
    int getSensorData();
    void updatePosition(Coord*);
    Coord getPosition();
    Sensor();
    ~Sensor();
};

//Register_Class(Sensor);
Define_Module(Sensor);

#endif /* SENSOR_H_ */
