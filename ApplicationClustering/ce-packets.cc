/*
 * ce-data.cpp
 *
 *  Created on: 28.08.2013
 *      Author: limir
 */

#include "ce-packets.h"


void MYCLASS packetsProcessMyPacket(GENERIC_PACKET * myPacket)
{
    simtime_t st =  simTime();
    volatile int vi = 0;
     if ((myNodeId == 5))
    {
         vi++;
    }
    switch (myPacket->packetType)
    {
        case PACKET_TYPE_NODE_REQUEST:  //or to resource manager
            resourceManagerApplicationRequest((PACKET_APPLICATION_REQUEST*) myPacket);
            break;
        case PACKET_TYPE_NODE_RESPONSE:
            coordinatorReceiveResponse((PACKET_APPLICATION_RESPONSE*) myPacket);
            break;
        case PACKET_TYPE_EVENT:
            coordinatorReceiveEvent((PACKET_EVENT*) myPacket);
            break;
        case PACKET_TYPE_APP_MASTER_REQUEST:
            appMasterReceiveRequestFromNet((PACKET_APPLICATION_MASTER_REQUEST*) myPacket);
            break;
        case PACKET_TYPE_APP_REQUEST:
            appManagerApplicationRequestFromNet((PACKET_APPLICATION*) myPacket);
            break;
        case PACKET_TYPE_APP_UPDATE:
            appManagerApplicationUpdate((PACKET_APPLICATION_UPDATE*) myPacket);
            break;
        case PACKET_TYPE_APP_EXECUTE:
            appManagerStartApplicationFromNet((PACKET_APPLICATION*) myPacket);
            break;
        case PACKET_TYPE_RESOURCE_REQUEST:
          resourceManagerRequest((PACKET_RESOURCE_REQUEST*) myPacket);
          break;
        case PACKET_TYPE_APP_MASTER_EVENT:
          appMasterReceiveEventFromNet((PACKET_APPLICATION_MASTER_EVENT*) myPacket);
          break;
        case PACKET_TYPE_APP_MASTER_1ST_EVENT:
          appMasterFirstClassReceiveEventFromNet((PACKET_APPLICATION_MASTER_1ST_EVENT*) myPacket);
          break;
        case PACKET_TYPE_DEBUG:
           break;
        case PACKET_TYPE_APP_MASTER_RESPONSE:
            coordinatorReceiveAppMasterResponse((PACKET_APP_MASTER_RESPONSE*) myPacket);
            break;
    }
        //printf("Receive Packet (Type 0x%02x) from 0x%04X\n", myPacket->packetType, myPacket->srcId);
    return;
}


void MYCLASS packetsProcessIncommingPacket(GENERIC_PACKET_RX * myPacket)
{
  if (myPacket->genericPacket.ttl>0x00)  //Time To Life
        myPacket->genericPacket.ttl--;
  else return;


  //Packet is type of routing --> Special Event !
  if(myPacket->genericPacket.dstId == myNodeId || myPacket->genericPacket.dstId == 0xFFFF )
  {
//      if (debugMode!=0)
//          printf("Receive a packet for me from 0x%04X\n",myPacket->rxSrcId);
      packetsProcessMyPacket(&myPacket->genericPacket);
  }
  return;
}
