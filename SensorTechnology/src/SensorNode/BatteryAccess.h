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

#ifndef ABSTRACTBATTERYACCESS_H_
#define ABSTRACTBATTERYACCESS_H_

#include <omnetpp.h>
#include <MiximBatteryAccess.h>
#include <string.h>

/**
 * this class gives access to the battery of the sensor node if you inherit from it
 *
 * extends the class MiximBatteryAccess by some useful functions like initialization
 *
 * it also stores values of consumption a module has and than can use this at any
 * time to draw energie by the stored amount
 */

#include "SensorNode.h"

class BatteryAccess : public MiximBatteryAccess {
protected:
    //int deviceID;
    SensorNode* getSensorNode();
public:
    float currentOverTime;
    float energiePerOperation;
    BatteryAccess();
    virtual ~BatteryAccess();
    void initialize(int stage);
    void say(const char *);
    void draw();
    void changeDrawCurrent(double cur, int acc);
    void changeEnergyConsumption(float);
    void finish();
    virtual void handleHostState(const HostState &state);
};

#endif /* ABSTRACTBATTERYACCESS_H_ */

