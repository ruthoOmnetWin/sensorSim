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

#ifndef ABSTRACTSENSINGUNIT_H_
#define ABSTRACTSENSINGUNIT_H_

#include <omnetpp.h>
#include <Coord.h>
#include <FindModule.h>
#include <BasePhyLayer.h>
#include <string.h>
#include "BatteryAccess.h"
#include "CustomWorldUtility.h"
#include "SimpleSensorData.h"

/**
 * simple implementation of the sensing unit which models
 * the power consumption and the sensing itself
 *
 * for the sensing it calls a function inside the world model and
 * gets a value by its type and position
 */
class AbstractSensingUnit : public BatteryAccess {
protected:
    Coord *Position;
    CustomWorldUtility *world;
    ChannelMobilityPtrType pMobType;
    std::string type;
protected:
    Coord* getLocation();
    int readData();
    ExtendedMessage* generateMessage(const char* msgname);
public:
    AbstractSensingUnit();
    virtual ~AbstractSensingUnit();
    void initialize(int stage);
    void readAndForward();
    void handleMessage(cMessage *msg);
};

Define_Module(AbstractSensingUnit);

#endif /* ABSTRACTSENSINGUNIT_H_ */
