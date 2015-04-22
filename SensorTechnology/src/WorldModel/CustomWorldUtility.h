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

#ifndef CUSTOMWORLDUTILITY_H_
#define CUSTOMWORLDUTILITY_H_

#include <BaseWorldUtility.h>
#include <omnetpp.h>
#include <string.h>
#include <StatisticsInterface.h>
#include <ExtendedMessage_m.h>

class CustomWorldUtility : public BaseWorldUtility, public StatisticsInterface
{
protected:
    int*** readXML(int);
    void setValue(int*** &parameter, int*** &data);
    void setTemperature();
    void setPressure();
    void setHumidity();
    void setLight();
    void initialize(int stage);
    ExtendedMessage* generateMessage(const char* msgname);
    void generateEnvironmentData();
    int* generateTemperature(int size);
    int* generatePressure(int size);
    int* generateHumidity(int size);
    int* generateLight(int size);
    void updateDisplay();
    void finish();
    void destroySensorData(int*** &);
protected:
    int numNodes;
    //sensor (world) data
    int*** temperatureArray;
    int*** pressureArray;
    int*** humidityArray;
    int*** lightArray;
    //meta information about data
    int sizeX;
    int sizeY;
    int sizeZ;
public:
    explicit CustomWorldUtility();
    virtual ~CustomWorldUtility();

    //"connection" to other modules
public:
    int getValueByPosition(std::string, Coord*);
};

Define_Module(CustomWorldUtility);

#endif /* CUSTOMWORLDUTILITY_H_ */
