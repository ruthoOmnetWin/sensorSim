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

#include <CSMA802154HostStateHandled.h>
#include "MacPkt_m.h"
#include "WiseRoutePkt_m.h"

Define_Module(CSMA802154HostStateHandled);

CSMA802154HostStateHandled::~CSMA802154HostStateHandled() {

}

CSMA802154HostStateHandled::CSMA802154HostStateHandled() {
    active = true;
}

void CSMA802154HostStateHandled::handleHostState(const HostState& state) {
    if(notAffectedByHostState)
        return;

    if(state.get() != HostState::ACTIVE) {
        active = false;
    } else {
        active = true;
    }
}

void CSMA802154HostStateHandled::initialize(int stage) {
    CSMA802154::initialize(stage);
    active = true;
}

cPacket* CSMA802154HostStateHandled::decapsMsg(macpkt_ptr_t macPkt) {
    if (active) {
        return CSMA802154::decapsMsg(macPkt);
    } else {
        //delete macPkt;
        return NULL;
    }
}

void CSMA802154HostStateHandled::handleLowerControl(cMessage *msg) {
    if (active) {
        CSMA802154::handleLowerControl(msg);
    } else {
        delete msg;
    }
}

void CSMA802154HostStateHandled::handleLowerMsg(cMessage *msg) {
    macpkt_ptr_t            macPkt     = static_cast<macpkt_ptr_t> (msg);
    const LAddress::L2Type& src        = macPkt->getSrcAddr();
    const LAddress::L2Type& dest       = macPkt->getDestAddr();
    long                    ExpectedNr = 0;

    debugEV<< "Received frame name= " << macPkt->getName()
    << ", myState=" << macState << " src=" << src
    << " dst=" << dest << " myAddr="
    << myMacAddr << endl;

    const char* name = macPkt->getName();
    if (strcmp(name, "wakeup") == 0) {
        sendUp(macPkt);
        return;
    }

    if(dest == myMacAddr)
    {
        if(!useMACAcks) {
            debugEV << "Received a data packet addressed to me." << endl;
//          nbRxFrames++;
            executeMac(EV_FRAME_RECEIVED, macPkt);
        }
        else {
            long SeqNr = macPkt->getSequenceId();

            if(strcmp(macPkt->getName(), "CSMA-Ack") != 0) {
                // This is a data message addressed to us
                // and we should send an ack.
                // we build the ack packet here because we need to
                // copy data from macPkt (src).
                debugEV << "Received a data packet addressed to me,"
                   << " preparing an ack..." << endl;

//              nbRxFrames++;

                if(ackMessage != NULL)
                    delete ackMessage;
                ackMessage = new MacPkt("CSMA-Ack");
                ackMessage->setSrcAddr(myMacAddr);
                ackMessage->setDestAddr(src);
                ackMessage->setBitLength(ackLength);
                //Check for duplicates by checking expected seqNr of sender
                if(SeqNrChild.find(src) == SeqNrChild.end()) {
                    //no record of current child -> add expected next number to map
                    SeqNrChild[src] = SeqNr + 1;
                    debugEV << "Adding a new child to the map of Sequence numbers:" << src << endl;
                    executeMac(EV_FRAME_RECEIVED, macPkt);
                }
                else {
                    ExpectedNr = SeqNrChild[src];
                    debugEV << "Expected Sequence number is " << ExpectedNr <<
                    " and number of packet is " << SeqNr << endl;
                    if(SeqNr < ExpectedNr) {
                        //Duplicate Packet, count and do not send to upper layer
                        nbDuplicates++;
                        executeMac(EV_DUPLICATE_RECEIVED, macPkt);
                    }
                    else {
                        SeqNrChild[src] = SeqNr + 1;
                        executeMac(EV_FRAME_RECEIVED, macPkt);
                    }
                }

            } else if(macQueue.size() != 0) {

                // message is an ack, and it is for us.
                // Is it from the right node ?
                macpkt_ptr_t firstPacket = static_cast<macpkt_ptr_t>(macQueue.front());
                if(src == firstPacket->getDestAddr()) {
                    nbRecvdAcks++;
                    executeMac(EV_ACK_RECEIVED, macPkt);
                } else {
                    EV << "Error! Received an ack from an unexpected source: src=" << src << ", I was expecting from node addr=" << firstPacket->getDestAddr() << endl;
                    delete macPkt;
                }
            } else {
                EV << "Error! Received an Ack while my send queue was empty. src=" << src << "." << endl;
                delete macPkt;
            }
        }
    }
    else if (LAddress::isL2Broadcast(dest)) {
        executeMac(EV_BROADCAST_RECEIVED, macPkt);
    } else {
        debugEV << "packet not for me, deleting...\n";
        delete macPkt;
    }
}
