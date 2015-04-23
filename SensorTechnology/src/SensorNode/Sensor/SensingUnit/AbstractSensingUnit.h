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
#include "AbstractBatteryAccess.h"
#include "CustomWorldUtility.h"
#include "SimpleSensorData.h"

class AbstractSensingUnit : public AbstractBatteryAccess {
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
};

Define_Module(AbstractSensingUnit);

#endif /* ABSTRACTSENSINGUNIT_H_ */
