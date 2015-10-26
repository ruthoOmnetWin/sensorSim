//
// Generated file, do not edit! Created by opp_msgc 4.3 from GenericPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include "ce-network.h"
#include "BaseModule.h"

#include "NetwControlInfo.h"
#include "Packet.h"
#include "BaseNetwLayer.h"
#include "FindModule.h"
#include "BaseWorldUtility.h"
#include "ApplPkt_m.h"
#include "SimpleAddress.h"

void MYCLASS networkSendPacketDirect(GENERIC_PACKET* myPacket,
        unsigned short destinationNode) {
    if (myPacket->ttl > 0x00)  //Time To Life
            {
        GenericPacket* gPacketP = new GenericPacket();

        //copy packet information
        gPacketP->setTtl(myPacket->ttl--);
        gPacketP->setSubType(myPacket->subType);
        gPacketP->setPacketType(myPacket->packetType);
        gPacketP->setPayloadsize(myPacket->payloadsize);

        gPacketP->setSrcId(myPacket->srcId);
        for (int i = 0; i < myPacket->payloadsize; i++)
            gPacketP->setData(i, myPacket->data[i]);
        gPacketP->setBitLength((myPacket->packetType + 8) * 8);

        if (myPacket->dstId == 0xFFFF)
        {
            gPacketP->setDstId(LAddress::L2BROADCAST);
            NetwControlInfo::setControlInfo(gPacketP, LAddress::L2BROADCAST);
        }
        else
        {
            gPacketP->setDstId(myPacket->dstId);
            NetwControlInfo::setControlInfo(gPacketP, destinationNode);
        }
        //Sending Packet
        double dr = ((double) (rand() % 0x100)) / 0x100;
        int di = rand() % 1000;
        dr = di;
        dr /=20000;
        simtime_t delay = dr;

        //TODO: selfmessage
        if (myPacket->dstId == myNodeId)
        {
            myBaseModule->scheduleAt(simTime() + delay,gPacketP );
            //myBaseModule->sendDelayed(gPacketP, delay, myOutGate);
        }
        else
        {
            myBaseModule->sendDelayed(gPacketP, delay, myOutGate);
        }


        //myBaseModule->send(gPacketP, myOutGate);
    } else {
        //if (debugMode!=0)
        printf("Dropping Packet for 0x%04X (TTL)\n", myPacket->dstId);
    }
    return;
}

void MYCLASS networkSendPacket(GENERIC_PACKET* myPacket) {
    networkSendPacketDirect(myPacket, myPacket->dstId);
}

