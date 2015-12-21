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

#ifndef MASTERCLUSTERAPPL_H_
#define MASTERCLUSTERAPPL_H_

#include <omnetpp.h>
#include <CustomDiceApplication.h>
#include <AbstractClusterAppl.h>
#include <ClusterApplWiseRoute.h>

class MasterClusterAppl : public CustomDiceApplication, public AbstractClusterAppl {
protected:
    cMessage* measuringTimer;
    int coordinatorNodeAddr;
    int measureTimerIntervall;
    ClusterApplWiseRoute* NetwLayer;
    void sendDiceEvent(void);

public:
    MasterClusterAppl();
    virtual ~MasterClusterAppl();
    void initialize(int stage);
    void handleMessage(cMessage* msg);
    void setNextEvent();
};

#endif /* MASTERCLUSTERAPPL_H_ */
