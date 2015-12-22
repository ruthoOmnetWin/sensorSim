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
#include <WiseRoutePkt_m.h>
#include <ArpInterface.h>

using std::make_pair;

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

void ClusterApplWiseRoute::handleLowerMsg(cMessage* msg) {
    //if message is not from my father or childs -> delete
    //if i am cluster master
    // -> forward messages from master
    // -> keep message that are addressed to me
    //if i am master or leaf -> never forward

    WiseRoutePkt* pkt = check_and_cast<WiseRoutePkt*>(msg);
    if (pkt != NULL) {
        LAddress::L3Type srcAddr = pkt->getSrcAddr();
        bool isNeighbour = isAddrFatherOrChild(srcAddr);
        if (!isNeighbour) {
            delete msg;
            return;
        }
    } else {
        opp_error("ClusterApplWiseRoute::handleLowerMsg() got an unknown message type.");
    }

    if (strcmp(msg->getName(), "WakeUpReceiverPacket") == 0) {

        WiseRoutePkt* pkt = check_and_cast<WiseRoutePkt*>(msg);
        WiseRoutePkt* copyPkt = pkt->dup();

        //pkt->setFinalDestAddr(LAddress::L3BROADCAST);

        sendUp(decapsMsg(pkt));
        if (isLeafClusterAppl || isMasterClusterAppl) {
            return;
        }

        //forward broadcast
        LAddress::L3Type finalDestAddr = copyPkt->getFinalDestAddr();
        LAddress::L3Type initialSrcAddr = copyPkt->getInitialSrcAddr();
        LAddress::L3Type destAddr = copyPkt->getDestAddr();
        LAddress::L3Type srcAddr = copyPkt->getSrcAddr();

        WakeUpPacket* wuPkt = new WakeUpPacket;
        wuPkt->setDestAddr(LAddress::L3BROADCAST);
        wuPkt->setSrcAddr(srcAddr);
        wuPkt->setName("WakeUpReceiverPacket");
        NetwControlInfo::setControlInfo(wuPkt, LAddress::L3BROADCAST);

        EV << "-------------------- I am NODE " << myNetwAddr << ". FORWARDING WakeUpReceiverPacket." << endl;

        if (LAddress::isL3Broadcast(finalDestAddr)) {
            //pkt->setFinalDestAddr();
            //NetwControlInfo::setControlInfo(copyPkt, LAddress::L3BROADCAST);
            //forward(wuPkt, srcAddr);
            handleUpperMsg(wuPkt);
        }

    } else
    if (strcmp(msg->getName(), "estimateResidualRelative") == 0) {
        EV << "Received message not to be forwarded" << endl;
        WiseRoutePkt* pkt = check_and_cast<WiseRoutePkt*>(msg);
        sendUp(decapsMsg(pkt));
    } else {
        if (strcmp(msg->getName(), "") != 0) {
            //opp_error("ClusterApplWiseRoute::handleLowerMsg() got an unknown message name.");
        }
        CustomWiseRoute::handleLowerMsg(msg);
    }
}

void ClusterApplWiseRoute::handleUpperMsg(cMessage* msg) {
    LAddress::L3Type finalDestAddr;
    LAddress::L3Type nextHopAddr;
    LAddress::L2Type nextHopMacAddr;
    WiseRoutePkt*    pkt   = new WiseRoutePkt(msg->getName(), DATA);
    cObject*         cInfo = msg->removeControlInfo();

    pkt->setByteLength(headerLength);

    if ( cInfo == NULL ) {
        EV << "WiseRoute warning: Application layer did not specifiy a destination L3 address\n"
           << "\tusing broadcast address instead\n";
        finalDestAddr = LAddress::L3BROADCAST;
    }
    else {
        EV <<"WiseRoute: CInfo removed, netw addr="<< NetwControlInfo::getAddressFromControlInfo( cInfo ) <<endl;
        finalDestAddr = NetwControlInfo::getAddressFromControlInfo( cInfo );
        delete cInfo;
    }

    pkt->setFinalDestAddr(finalDestAddr);
    pkt->setInitialSrcAddr(myNetwAddr);
    pkt->setSrcAddr(myNetwAddr);
    pkt->setNbHops(0);

    if (LAddress::isL3Broadcast(finalDestAddr))
        nextHopAddr = LAddress::L3BROADCAST;
    else
        nextHopAddr = getRoute(finalDestAddr, true);
    pkt->setDestAddr(nextHopAddr);
    if (LAddress::isL3Broadcast(nextHopAddr)) {
        // it's a flood.
        nextHopMacAddr = LAddress::L2BROADCAST;
        pkt->setIsFlood(1);
        nbFloodsSent++;
        // record flood in flood table
        floodTable.insert(make_pair(myNetwAddr, floodSeqNumber));
        pkt->setSeqNum(floodSeqNumber);
        floodSeqNumber++;
        nbGetRouteFailures++;
    }
    else {
        pkt->setIsFlood(0);
        nbPureUnicastSent++;
        nextHopMacAddr = arp->getMacAddr(nextHopAddr);
    }
    setDownControlInfo(pkt, nextHopMacAddr);
    assert(static_cast<cPacket*>(msg));
    pkt->encapsulate(static_cast<cPacket*>(msg));
    sendDown(pkt);
    nbDataPacketsSent++;
}
