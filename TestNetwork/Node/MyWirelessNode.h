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
#include <ExtendedMessage_m.h>
#include <StatisticsInterface.h>
#include <SimpleSensorType.h>

class MyWirelessNode : public Sensor, public StatisticsInterface     //cCompoundModule public cSimpleModule,
{
protected:
    void initialize(int stage);
    void handleMessage(cMessage *msg);
    void finish();
    void updateDisplay();
    void findSensorType();
    void sendDataRequest(std::string);
    void handleGetType(cMessage *msg);
    void requestData();
    ExtendedMessage* generateMessage(const char* msgname);
    bool isPositive(int value);
    int readSensor();
protected:
    cModuleType *componenttype;
    Coord* position;
    SensorType* type;
    int temperatureData;
    int pressureData;
    int lightData;
    int humidityData;
public:
    void updatePosition();
    explicit MyWirelessNode();
    virtual ~MyWirelessNode();
    int getSensorData();
    std::string* typenames;
};

#endif /* MYWIRELESSNODE_H_ */
