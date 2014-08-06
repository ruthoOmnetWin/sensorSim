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
#include <omnetpp.h>
#include <CustomLinearMobility.h>
#include <Coord.h>

class MyWirelessNode : public Sensor     //cCompoundModule public cSimpleModule,
{
private:
    long numSent;
    long numReceived;
protected:
    void initialize(int stage);
    void handleMessage(cMessage *msg);
    void finish();
    int readSensor();
    cModuleType *componenttype;
protected:
    Coord* position;
    void updateDisplay();
public:
    void updatePosition();
    MyWirelessNode();
    ~MyWirelessNode();
    int getSensorData();
};

#endif /* MYWIRELESSNODE_H_ */
