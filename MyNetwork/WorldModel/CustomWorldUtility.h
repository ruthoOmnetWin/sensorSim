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

class MIXIM_API CustomWorldUtility : public BaseWorldUtility
{
protected:
    int numNodes;
    int* temperatureArray;
    int tempLength;
    int* pressureArray;
    int pressLength;
    int* readXML(int);
    void setTemperature();
    void setPressure();
    void initialize(int stage);
    void handleMessage(cMessage *msg);
    void generateEnvironmentData();
    int* generateTemperature(int size);
    int* generatePressure(int size);
    int* generateHumidity(int size);
public:
    CustomWorldUtility();
    ~CustomWorldUtility();
};

Define_Module(CustomWorldUtility);

#endif /* CUSTOMWORLDUTILITY_H_ */
