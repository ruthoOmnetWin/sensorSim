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

#ifndef ABSTRACTSIGNALCONVERTER_H_
#define ABSTRACTSIGNALCONVERTER_H_

#include <omnetpp.h>
#include "AbstractBatteryAccess.h"

/**
 * simple implementation of the signal converter which just models
 * the power consumption yet
 */
class AbstractSignalConverter : public AbstractBatteryAccess {
public:
    AbstractSignalConverter();
    virtual ~AbstractSignalConverter();
    void handleMessage(cMessage *msg);
};

Define_Module(AbstractSignalConverter)

#endif /* ABSTRACTSIGNALCONVERTER_H_ */
