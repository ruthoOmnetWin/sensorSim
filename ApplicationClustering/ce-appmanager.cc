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

void MYCLASS appManagerInit(void)
{
    unsigned int i, j;
//Set resource map
    i = rand() % 700 + 300;
    j = rand() % 1000;

    //i = randomGetLimit(700) + 300;  j = randomGetLimit(1000);
    //appschedulerInsertAppEntry(META_LED4_FLASH, APP_STATE_INIT, myNodeId, 0, i, j, 20, 0, 0); //B

}

unsigned int MYCLASS appManagerGetLocalAppId(unsigned int globalAppId)
{
    if (globalAppId < 7 && globalAppId > 0)
    {
        return META_LED4_FLASH;
    }
    return 0;
}

void MYCLASS appManagerReorg(void)
{

}

void MYCLASS appManagerCheck(void)  //call only from main() !!!
{
    unsigned int i;
    volatile int debug;
    //reorg

    APP_STRUCT* myAppStruct = NULL;
    appFirstEntry = NULL;

    for (i = 0; i < APP_LISTCOUNT; i++)
    {
        myAppStruct = &appList[i];
        myAppStruct->nextAppStruct = NULL;
        myAppStruct->lastAppStruct = NULL;
        if (myAppStruct->status == APP_STATE_SUSPEND)     //remove from scheduler, release some resources;
        {
            myAppStruct->status = APP_STATE_SUSPENDED;
        }
        else if (myAppStruct->status == APP_STATE_REMOVE)   //remove from scheduler
        {
            //free resources
            resourceManagerFree(myAppStruct);

            if (myAppStruct->options & OPTIONS_MASTER_INFORMATION)  //info to master of this app
            {
                appManagerSendResponse(i, myAppStruct->master, 0, RESPONSE_DELETED);

            }
            myAppStruct->status = APP_STATE_DELETED;
            //myBaseHost->getDisplayString().setTagArg("i2", 0, "");
            //myBaseHost->getDisplayString().setTagArg("i2", 0, "status/red");

        }
        else if (myAppStruct->status == APP_STATE_READY || myAppStruct->status == APP_STATE_INIT)
        {
            appschedulerCalcNextExecution(myAppStruct);
            appschedulerInsertPosition(myAppStruct);
            //appList[i].status = APP_STATE_READY;
        }
        else
        {
            debug++;
        }
    }
    if (appFirstEntry != NULL)
    {
        //setting the timer
        clusterApplicationUpdateTimer(TIMER_ID_APPLICATION_SCHEDULER, TIMER_TYPE_SET, appFirstEntry->start);
    }
    else
    {
        clusterApplicationUpdateTimer(TIMER_ID_APPLICATION_SCHEDULER, TIMER_TYPE_DELETE, 0);
    }
}

void MYCLASS appManagerApplicationUpdate(PACKET_APPLICATION_UPDATE* myApplicationPacket)
{
    APP_STRUCT* myAppStruct;
    unsigned int i;
    switch (myApplicationPacket->update)
    {
        case PACKET_SUBTYPE_APP_STOP_DEL_1:  //p->application => pos in appList
            if (myApplicationPacket->application < APP_LISTCOUNT)
            {
                myAppStruct = &appList[myApplicationPacket->application];
                if (myAppStruct->meta == 0)
                {
                    appschedulerRemoveApp(myAppStruct);
                }
                else
                {
                    myAppStruct->count = 1;
                }
                appManagerSendResponse(i, myApplicationPacket->srcId, 0, RESPONSE_MARKED);
                break;
            }
            appManagerSendResponse(myApplicationPacket->application, myApplicationPacket->srcId, 0, RESPONSE_FAIL);
        case PACKET_SUBTYPE_APP_DELETE_1:  //p->application => pos in appList
            if (myApplicationPacket->application < APP_LISTCOUNT)
            {
                myAppStruct = &appList[myApplicationPacket->application];
                appschedulerRemoveApp(myAppStruct);
                appManagerSendResponse(i, myApplicationPacket->srcId, 0, RESPONSE_DELETED);
                break;
            }
            appManagerSendResponse(myApplicationPacket->application, myApplicationPacket->srcId, 0, RESPONSE_FAIL);
        case PACKET_SUBTYPE_APP_DELETE_2:  //p->application => appId (enum)
            for (i = 0; i < APP_LISTCOUNT; i++)
            {
                if (myApplicationPacket->application == 0)
                    break;
                if ((appList[i].appId == myApplicationPacket->application) && (appList[i].status != APP_STATE_DELETED))
                {
                    myAppStruct = &appList[i];
                    appschedulerRemoveApp(myAppStruct);
                    break;
                }
            }
            if (i >= APP_LISTCOUNT)
                appManagerSendResponse(myApplicationPacket->application, myApplicationPacket->srcId, 0, RESPONSE_FAIL);
            else
                appManagerSendResponse(myApplicationPacket->application, myApplicationPacket->srcId, 0,
                        RESPONSE_DELETED);
            break;
        case PACKET_SUBTYPE_APP_RESTART:


            break;
        default:
            break;
    }
}

/*
 void ClusterApplication::appManagerStartLocalApplication(unsigned int appId)
 {
 switch (appID)
 {

 appschedulerInsertAppEntry(,
 APP_STATE_INIT,        //Ohne INIT
 myApplicationPacket->srcId, myApplicationPacket->count, myApplicationPacket->delay,
 myApplicationPacket->start, myApplicationPacket->parameterA, myApplicationPacket->parameterB,
 myApplicationPacket->options);
 break;
 case 2:
 }
 }
 */
void MYCLASS appManagerApplicationRequest(PACKET_APPLICATION_REQUEST* myRequestPacket)
{

// Check if this application is executable on this node
// Response to the coordinator node

    /*
     PACKET_APPLICATION_REQUEST* requestPacketP = (PACKET_APPLICATION_REQUEST*) &txPacketPrepare.genericPacket;
     requestPacketP->srcId = myNodeId;
     requestPacketP->dstId = 0xFFFF;
     requestPacketP->ttl = DEFAULT_TTL;
     requestPacketP->packetType = PACKET_TYPE_NODE_REQUEST;
     requestPacketP->payloadsize = sizeof(PACKET_APPLICATION_REQUEST) - HEADERSIZE ;
     requestPacketP->application = application;
     requestPacketP->reference = reference;
     requestPacketP->request = request;
     networkSendPacket((GENERIC_PACKET*) requestPacketP);
     */

}

void MYCLASS appManagerApplicationRequestFromNet(PACKET_APPLICATION* myApplicationPacket)
{
    volatile int i;
    i++;
    return;
}

void MYCLASS appManagerSendResponse(unsigned int id, unsigned int destination, unsigned int ref,
        unsigned char response)
{
    PACKET_APPLICATION_RESPONSE* dataPacketP = (PACKET_APPLICATION_RESPONSE*) &txPacketPrepare.genericPacket;
    dataPacketP->dstId = destination;
    dataPacketP->srcId = myNodeId;
    dataPacketP->packetType = PACKET_TYPE_APP_RESPONSE;
    dataPacketP->subType = 0;
    dataPacketP->response = response;
    dataPacketP->appId = id;
    dataPacketP->reference = ref;
    dataPacketP->storage = 0;

    //TODO //only UART
    //queueInsertObjectSpecial(&txUartQueue,dataPacketP,sizeof(PACKET_APPLICATION_RESPONSE));

    ////networkSendPacketDirect(GENERIC_PACKET* myPacket,unsigned short destinationNode);
    return;
}

void MYCLASS appManagerStartApplicationFromNet(PACKET_APPLICATION* myApplicationPacket)
{
    unsigned int id, tmp;
    unsigned char response = RESPONSE_FAIL;
//Resource Check

//Insert Check

//unsigned char appId,unsigned char status,unsigned char count,unsigned long delay,unsigned long start,unsigned int parameterA,unsigned int parameterB)

    id = appschedulerInsertAppEntry(myApplicationPacket->appId,
            APP_STATE_CHECK,        //Ohne INIT
            myApplicationPacket->srcId, myApplicationPacket->count, myApplicationPacket->delay,
            myApplicationPacket->start, myApplicationPacket->parameterA, myApplicationPacket->parameterB,
            myApplicationPacket->options);
    if (id != 0xFFFF)
    {
        //APP_STRUCT* myAppStruct;myAppStruct = ;
        tmp = resourceManagerAllocate((APP_STRUCT*) &appList[id]);
        if (tmp == 2)
        {
            response = RESPONSE_STARTED;
            appList[id].status = APP_STATE_INIT;
            appschedulerCalcNextExecution(&appList[id]);
            appschedulerInsertPosition(&appList[id]);
        }
        else if (tmp == 1)
        {
            response = RESPONSE_RESOURCE_ERROR;
            appList[id].status = APP_STATE_DELETED;
        }

    }

    appManagerSendResponse(id, myApplicationPacket->srcId, 0, response);
    //send response
}
