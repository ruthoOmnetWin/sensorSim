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

#include <ClusterApplWiseRoute.h>
#include <FindModule.h>
#include <LeafClusterAppl.h>
#include <ClusterMasterClusterAppl.h>
#include <MasterClusterAppl.h>

Define_Module(ClusterApplWiseRoute);

LAddress::L3Type ClusterApplWiseRoute::getMyNetworkAddress() {
    return myNetwAddr;
}

void ClusterApplWiseRoute::initialize(int stage) {
    CustomWiseRoute::initialize(stage);
    if (stage == 1){

        isMasterClusterAppl = false;
        isLeafClusterAppl = false;
        isClusterMasterClusterAppl = false;

        appl = FindModule<AbstractClusterAppl*>::findSubModule(findHost());
        if (dynamic_cast<LeafClusterAppl*>(appl) != NULL) {
            isLeafClusterAppl = true;
        } else if (dynamic_cast<ClusterMasterClusterAppl*>(appl) != NULL) {
            isClusterMasterClusterAppl = true;
        } else if (dynamic_cast<MasterClusterAppl*>(appl) != NULL) {
            isMasterClusterAppl = true;
        } else {
            opp_error("Inside ClusterApplWiseRoute::initialize(): Could not get the type of the Application Layer. There was an invalid type given.");
        }
    }
}
