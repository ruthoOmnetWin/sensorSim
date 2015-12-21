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

#include <ClusterMasterClusterAppl.h>
#include <FindModule.h>
#include "ModuleAccess.h"
#include <string.h>

Define_Module(ClusterMasterClusterAppl);

ClusterMasterClusterAppl::ClusterMasterClusterAppl() {
}

ClusterMasterClusterAppl::~ClusterMasterClusterAppl() {
}

void ClusterMasterClusterAppl::initialize(int stage) {
    if (stage == 1) {
        NetwLayer = FindModule<ClusterApplWiseRoute*>::findSubModule(findHost());
        childNodes = NetwLayer->getChildNodes(NetwLayer->getMyNetworkAddress());

        do {
            if (childNodes->value != -1) {

                std::stringstream ss;
                ss << "Node" << childNodes->value;
                cModule* node = findModuleWherever(ss.str().c_str(), findHost()->getParentModule());

                SensorNode* sNode = dynamic_cast<SensorNode*>(node);
                if (sNode != NULL) {
                    SensorTypeInformation* sti = new SensorTypeInformation;
                    sti->nodeNetwAddr = childNodes->value;
                    sti->nodeObject = sNode;

                    sti->hasTemperatureSensor = sNode->par("hasTemperatureSensor");
                    sti->hasHumiditySensor = sNode->par("hasHumiditySensor");
                    sti->hasPressureSensor = sNode->par("hasPressureSensor");
                    sti->hasLightSensor = sNode->par("hasLightSensor");
                    SensorTypeInformationVector.push_back(*sti);
                }

            }
            childNodes = childNodes->next;
        } while (childNodes != NULL);
    }
}

void ClusterMasterClusterAppl::handleMessage(cMessage* msg) {
    //todo get battery status of all my leafs -> this must be done per message
}
