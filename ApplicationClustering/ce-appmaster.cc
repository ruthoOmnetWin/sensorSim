//
// Generated file, do not edit! Created by opp_msgc 4.3 from GenericPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include "ce-data.h"
#include "ce-clusterApplication.h"

void MYCLASS appMasterInit(void)
{

}

unsigned char MYCLASS appMasterChoiceNodes(unsigned int applicationId,PACKET_APPLICATION_MASTER_REQUEST* myEventPacket,  unsigned int nodes[])
{
    unsigned int tmpGrp=0;
    unsigned int nodes_backup[20];
    unsigned int nodeCnt_backup;
    const char appLocMat[7][10] =
        {
                //pos 0 -->
//                0  1  2  3  4  5  6  7  8  9
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //0
                { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 }, //1
                { 0, 2, 0, 1, 0, 0, 0, 1, 0, 2 }, //2
                { 0, 2, 0, 1, 0, 3, 0, 1, 0, 2 }, //3
                { 0, 1, 0, 1, 0, 0, 0, 1, 0, 1 }, //4
                { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 }, //5
                { 0, 3, 2, 3, 1, 0, 1, 3, 2, 3 }  //6
        };
    unsigned char nodeCnt=0;
    unsigned int sumEnergy=0;
    unsigned int sumEnergy_backup = 0;
    unsigned int energyMin = 0xFFFF;    // not used at this time
    unsigned int energyMax = 0;         // not used at this time


    for (tmpGrp=1;tmpGrp<255;tmpGrp<<=1)  //suche nach möglichen gruppen
    {
        nodeCnt_backup=0; //find the next constellation
        sumEnergy_backup=0;
        for (int i =0;i<10;i++)  //erste Möglichkeit finden
        {
            //durchlaufen der appLocMat, suche nach einer Zahl und allen möglichen Knoten
            if ((appLocMat[applicationId][i] & tmpGrp) == tmpGrp)
            {
                int cnt = (myEventPacket->payloadsize - 8) / sizeof(XMIT_NODE_ENTRY);
                for (int entry=0;entry<cnt;entry++)
                {
                    if (
                            (myEventPacket->nodeEntries[entry].resourceId == RESOURCE_ID_LOCATION) &&  // don't search for id
                            ((myEventPacket->nodeEntries[entry].resourceValue & 0x0F ) == i)
                            )
                    {
                        unsigned int energy;
                        energy = myEventPacket->nodeEntries[entry].resourceSum;
                        nodes_backup[nodeCnt_backup++] = myEventPacket->nodeEntries[entry].nodeId;
                        if (energy>energyMax) energyMax = energy;
                        if (energy<energyMin) energyMin = energy;
                        sumEnergy_backup += energy;

                        break;
                    }
                }
            }
            if (nodeCnt_backup>=applicationId)
                break;
        }


        if ((nodeCnt_backup>=applicationId) && (sumEnergy_backup>=sumEnergy))
        {
            //found a solution
            //check the energy and test the next better combination
            for (int i=0;i<nodeCnt_backup;i++)
            {
                nodes[i]=nodes_backup[i];
            }
            nodeCnt = nodeCnt_backup;
            sumEnergy = sumEnergy_backup;

            //return nodeCnt;
            //break;

        }
    }

    if ((nodeCnt>=applicationId))
    {
        return nodeCnt;
    }
    return 0;
}


void MYCLASS appMasterReceiveRequestFromNet(PACKET_APPLICATION_MASTER_REQUEST* myEventPacket)
{
    unsigned int nodes[11];
    unsigned int nodeCnt;
    unsigned int tmp;
    PACKET_APPLICATION* packetApplicationP = (PACKET_APPLICATION*) &txPacket.genericPacket;
    PACKET_APP_MASTER_RESPONSE* packetResponseP = (PACKET_APP_MASTER_RESPONSE*) &txPacket.genericPacket;
    // test if the application is local runnable --> best master was already selected
    nodeCnt = appMasterChoiceNodes(myEventPacket->application, myEventPacket,nodes);
    // for this application groups are needed.


    //TODO: Remove on real hardware
    //clusterApp->myBaseHost->getDisplayString().setTagArg("i", 0, bubblestr);
    //findHost()->getDisplayString().setTagArg("i2", 0, "status/red");

    //clusterApp->myBaseHost->getDisplayString().setTagArg("i", 0, bubblestr);
    myBaseHost->getDisplayString().setTagArg("i2", 0, "status/red");






    //send Application to all selected nodes
    for (unsigned int i =0 ; i<nodeCnt; i++)
    {
        if (nodes[i]!=myNodeId)      //if local node is selected, start local app, else sendMessage
        {
                packetApplicationP->packetType = PACKET_TYPE_APP_EXECUTE;
                packetApplicationP->dstId = nodes[i];
                packetApplicationP->ttl = DEFAULT_TTL;
                packetApplicationP->srcId = myNodeId;
                packetApplicationP->payloadsize = sizeof(PACKET_APPLICATION);
                packetApplicationP->options = 0;
                packetApplicationP->appId = appManagerGetLocalAppId(myEventPacket->application);
                packetApplicationP->count = 50;
                packetApplicationP->delay = 0;
                packetApplicationP->parameterA = 100;
                packetApplicationP->parameterB = 100;
                packetApplicationP->start = ticks+100;  // now + 50ms
                packetApplicationP->id = 0;
                networkSendPacketDirect((GENERIC_PACKET*) packetApplicationP, nodes[i]);
        }
        else
        {
            /*unsigned int ClusterApplication::appschedulerInsertAppEntry(unsigned char appId, unsigned char status,
        unsigned int master, unsigned char count, unsigned long delay, unsigned long start, unsigned int parameterA,
        unsigned int parameterB, unsigned char options)*/

            tmp = appManagerGetLocalAppId(myEventPacket->application);
            appschedulerInsertAppEntry(
                    tmp, APP_STATE_INIT, //appId, INIT
                    myNodeId,            //master
                    50, 0, ticks+100, //count,delay,start
                    100, 100, 0
            ); //paramA,paramB,opt
        }
    }


    // TODO: setup application --> generate application from event/appid ???

    // TODO: setup update process to coordinator -->
    // Response to Coordinator

    //
    packetResponseP->packetType = PACKET_TYPE_APP_MASTER_RESPONSE;
    packetResponseP->dstId = myEventPacket->srcId;
    packetResponseP->ttl = DEFAULT_TTL;
    packetResponseP->srcId = myNodeId;
    packetResponseP->payloadsize = sizeof(PACKET_APP_MASTER_RESPONSE);

    packetResponseP->application = myEventPacket->application; //global App
    packetResponseP->timestamp = ticks;
    packetResponseP->response = RESPONSE_OK_AND_FORGET;
    packetResponseP->expire = ticks+200;
    packetResponseP->application = myEventPacket->application;
    packetResponseP->reference = myEventPacket->reference;
    //packetResponseP
    networkSendPacketDirect((GENERIC_PACKET*) packetResponseP,myEventPacket->srcId); //TODO: send to Coordinator-Id


    //appschedulerInsertAppEntry(META_LED4_FLASH,APP_STATE_INIT,myNodeId,0,i,j,20,0,0); //B
/*
    appschedulerInsertAppEntry(
        META_LED4_FLASH,
        APP_STATE_INIT,
        myNodeId,
        10,
        rand() % 500 + 300,       //randomGetLimit(500) + 300,
        rand() % 1000,  //randomGetLimit(1000),
        20,0,0); //B
*/
}




unsigned int MYCLASS appMasterReceiveEventFromNet(PACKET_APPLICATION_MASTER_EVENT* myEventPacket)
{
// An event was transmitted from other sensor node to this


// look in the event table for choice the correct response


// FOR NANETT
// The die is cast. At top are xxx.
    switch (myEventPacket->event)
    {
      case DIE_EVENT_1:
        break;
      case DIE_EVENT_2:
        break;
      case DIE_EVENT_3:
        break;
      case DIE_EVENT_4:
        break;
      case DIE_EVENT_5:
        break;
      case DIE_EVENT_6:
        break;
      default:  // unknown event
        return 0;
        break;
    }
    return 1;
}


void MYCLASS appMasterReceiveEventFromLocale(void)
{

}

void MYCLASS appMasterFirstClassReceiveEventFromNet(PACKET_APPLICATION_MASTER_1ST_EVENT* myEventPacket)   // 0x57
{
    //search local for knowledge of this event
    if (appMasterReceiveEventFromNet((PACKET_APPLICATION_MASTER_EVENT*) myEventPacket) != 0)
    {
        // TODO: do something
        return;  //local is possible
    }

    //search event master --> local database ?
    //
    //FIXME don't broadcast here, ask only the NetworkClusterMaster !!!
    appMasterRequestMaster(myEventPacket->event,0xFFFF, myEventPacket->random);
}


void MYCLASS appMasterFirstClassReceiveEventFromLocale(void)
{

}


void MYCLASS appMasterReceiveResponse(void)
{


}



void MYCLASS appMasterRequestMaster(unsigned int event, unsigned int destination, unsigned int response)
{
  PACKET_APPLICATION_MASTER_EVENT* eventPacketP = (PACKET_APPLICATION_MASTER_EVENT*) &txPacketPrepare.genericPacket;
  eventPacketP->dstId = destination;
  eventPacketP->srcId = myNodeId;
  eventPacketP->packetType = PACKET_TYPE_APP_MASTER_EVENT;
  eventPacketP->subType = 0x01;  //Request for new masters
  eventPacketP->random = response;
  eventPacketP->payloadsize = 8;
  eventPacketP->ttl = 0x10;
  eventPacketP->event = event;
  eventPacketP->random = response;
  //TODO //only UART
  //networkSendPacket()


  //FIXME don't broadcast here, ask only the NetworkClusterMaster !!!
  networkSendPacketDirect((GENERIC_PACKET*) eventPacketP, destination);

  //queueInsertObjectSpecial(&txQueue,eventPacketP,sizeof(PACKET_APPLICATION_MASTER_1ST_EVENT));
  //networkSendPacketDirect(GENERIC_PACKET* myPacket,unsigned short destinationNode);
}

