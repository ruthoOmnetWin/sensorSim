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

#include <NoApplicationClusteringAppl.h>
#include <FindModule.h>

Define_Module(NoApplicationClusteringAppl);

void NoApplicationClusteringAppl::initialize(int stage) {
    //params
    coordinatorNodeAddr = par("coordinatorNodeAddr");
    sendSensorDataToMasterIntervall = par("sendingIntervall");
    //selfmessage sendToMaster init
    sendToMaster = new cMessage("sendToMaster");
    scheduleAt(simTime() + sendSensorDataToMasterIntervall + 1, sendToMaster);

    //memory
    memory = FindModule<Memory*>::findSubModule(findHost());
}

void NoApplicationClusteringAppl::handleMessage(cMessage* msg) {
    if (msg->isSelfMessage()) {
        if (strcmp(msg->getName(), sendToMaster->getName()) == 0) {
            //memory auslesen und leeren
            storage* sensorData = memory->readAllAndClear();
            //sende message an den coordinator node mit messungen

            //forward selfmessage
            scheduleAt(simTime() + sendSensorDataToMasterIntervall, sendToMaster);
        }
    }
}
