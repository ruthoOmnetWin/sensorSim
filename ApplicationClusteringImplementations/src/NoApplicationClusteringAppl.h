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

#ifndef NOAPPLICATIONCLUSTERINGAPPL_H_
#define NOAPPLICATIONCLUSTERINGAPPL_H_

#include <omnetpp.h>
#include <BaseModule.h>
#include <Memory.h>

class NoApplicationClusteringAppl : public BaseModule
{
    int coordinatorNodeAddr;
    int sendSensorDataToMasterIntervall;
    Memory* memory;
public:
    cMessage* sendToMaster;
    void initialize(int stage);
    void handleMessage(cMessage* msg);
};

#endif /* NOAPPLICATIONCLUSTERINGAPPL_H_ */
