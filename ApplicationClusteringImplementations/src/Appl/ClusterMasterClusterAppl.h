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

#ifndef CLUSTERMASTERCLUSTERAPPL_H_
#define CLUSTERMASTERCLUSTERAPPL_H_

#include <omnetpp.h>
#include <BaseModule.h>
#include <AbstractClusterAppl.h>
#include <ClusterApplWiseRoute.h>
#include <SensorNode.h>
#include <vector>
#include <CustomMatrixApplication.h>

class ClusterMasterClusterAppl : public CustomMatrixApplication, public AbstractClusterAppl {
protected:
    ClusterApplWiseRoute* NetwLayer;

    CustomWiseRoute::AdjListElement* childNodes;

public:
    ClusterMasterClusterAppl();
    virtual ~ClusterMasterClusterAppl();
    void initialize(int stage);
    void handleMessage(cMessage* msg);

    struct SensorTypeInformation {
        int nodeNetwAddr = -1;
        SensorNode* nodeObject = NULL;
        bool hasTemperatureSensor = false;
        bool hasHumiditySensor = false;
        bool hasPressureSensor = false;
        bool hasLightSensor = false;
    };

    std::vector<SensorTypeInformation> SensorTypeInformationVector;

};

#endif /* CLUSTERMASTERCLUSTERAPPL_H_ */
