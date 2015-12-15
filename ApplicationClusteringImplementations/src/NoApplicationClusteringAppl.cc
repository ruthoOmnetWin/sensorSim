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
#include <ApplPkt_m.h>
#include <SimpleSensorData.h>
#include <NetwControlInfo.h>

Define_Module(NoApplicationClusteringAppl);

NoApplicationClusteringAppl::NoApplicationClusteringAppl() {
    iAmLeafNode = false;
    myNetworkAddr = 0;
}

NoApplicationClusteringAppl::~NoApplicationClusteringAppl() {
    iAmLeafNode = false;
    myNetworkAddr = 0;
}

void NoApplicationClusteringAppl::initialize(int stage) {
    if (stage == 0) {
        //gates
        dataOut = findGate("lowerLayerOut");
        dataIn = findGate("lowerLayerIn");
        ctrlOut = findGate("lowerControlOut");
        ctrlIn = findGate("lowerControlIn");
        //params
        coordinatorNodeAddr = par("coordinatorNodeAddr");
        sendSensorDataToMasterIntervall = par("sendingIntervall");
    }
    if (stage == 1) {

        if (iAmLeafNode) {
            //selfmessage sendToMaster init
            sendToMaster = new cMessage("sendToMaster");
            //nodes should send one after another and all at the same time so the receiver can receive all messages correctly
            scheduleAt(simTime() + sendSensorDataToMasterIntervall + 1 + (0.02 * myNetworkAddr), sendToMaster);
        }

        //memory
        memory = FindModule<Memory*>::findSubModule(findHost());
    }
}

void NoApplicationClusteringAppl::handleMessage(cMessage* msg) {
    if (msg->isSelfMessage()) {
        if (strcmp(msg->getName(), sendToMaster->getName()) == 0) {
            //memory auslesen und leeren
            int size = memory->getDataSizeCount();
            storage* sensorData = memory->readAllAndClear();
            //sende message an den coordinator node mit messungen
            ApplPkt* dataMessage = new ApplPkt();
            LAddress::L3Type dest = coordinatorNodeAddr;
            dataMessage->setDestAddr(dest);
            NetwControlInfo::setControlInfo(dataMessage, dest);
            dataMessage->setName("sensor data");
            //cArray parList = dataMessage->getParList();

            for (int i = 0; i < size; i++) {
                SimpleSensorData* tmp = new SimpleSensorData(sensorData[i].type.c_str(), sensorData[i].value);
                dataMessage->getParList().add(tmp);
            }

            int i = 0;
            while (dataMessage->getParList().exist(i)) {
                //pkt->getParList().add(parlist->get(i));
                i++;
            }

            send(dataMessage, dataOut);
            //forward selfmessage
            scheduleAt(simTime() + sendSensorDataToMasterIntervall, sendToMaster);
        }
    } else {
        if (myNetworkAddr == coordinatorNodeAddr) {
            EV << "============= Coordinator: Received external Message" << endl;
        } else {
            EV << "============= Non-Coordinator: Received external Message" << endl;
        }

        cArray parList = msg->getParList();

        int i = 0;
        while(msg->getParList().exist(i)) {
            cObject* tmp = parList.get(i);
            i++;
        }

        //forEachChild
    }
}
