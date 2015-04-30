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

#ifndef ABSTRACTSIGNALCONDITIONER_H_
#define ABSTRACTSIGNALCONDITIONER_H_

#include <omnetpp.h>
#include "BatteryAccess.h"

/**
 * simple implementation of the signal conditioner which just models
 * the power consumption yet
 */
class AbstractSignalConditioner : public BatteryAccess {
public:
    AbstractSignalConditioner();
    virtual ~AbstractSignalConditioner();
    void handleMessage(cMessage *msg);
};

Define_Module(AbstractSignalConditioner);

#endif /* ABSTRACTSIGNALCONDITIONER_H_ */
