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

#ifndef LEAFCLUSTERAPPL_H_
#define LEAFCLUSTERAPPL_H_

#include <omnetpp.h>
#include <SimpleBattery.h>
#include <AbstractClusterAppl.h>
#include <Memory.h>
#include <Processor.h>
#include <CustomMatrixApplication.h>

class LeafClusterAppl : public CustomMatrixApplication, public AbstractClusterAppl {
protected:
    SimpleBattery* battery;
    Processor* processor;
    Memory* memory;

    bool hasTemperatureSensor;
    bool hasHumiditySensor;
    bool hasPressureSensor;
    bool hasLightSensor;

    void sendBatteryStatus(int target);
public:
    LeafClusterAppl();
    virtual ~LeafClusterAppl();
    void initialize(int stage);
    void handleMessage(cMessage* msg);

    int roomNumber;
    int roomId;
};

#endif /* LEAFCLUSTERAPPL_H_ */
