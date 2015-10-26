/*
 * ce-data.cpp
 *
 *  Created on: 28.08.2013
 *      Author: limir
 */

#include "ce-coordinator.h"
#include "ce-clusterApplication.h"

unsigned short getAppGroup(unsigned int event)
{
    return 0x1001; // unique network wide application
}

unsigned int getGlobalAppId(unsigned int event)
{
    if (event < 7 && event > 0)
        return event;
    return 0;
}

//Receive Events
void MYCLASS coordinatorReceiveEvent(PACKET_EVENT* myEventPacketP)
{
    int i = 0;
    PACKET_APPLICATION_RESPONSE* p;
    PACKET_APPLICATION_UPDATE* updatePacketP = (PACKET_APPLICATION_UPDATE*) &txPacketPrepare.genericPacket;
    unsigned char nextEntry = 0xFF;
    unsigned short appGroup = getAppGroup(myEventPacketP->event);
    //search in list for running apps with this triggered event

    //ask for app / event

    for (i = 0; i < COORDINATOR_APP_ENTRIES; i++)
    {

        //TODO: search for incompatible events  (i.e. Display1 vs. Display2...)
        //use Event/App Groups
        //kill these events

        if ((CoordinatorAppList[i].event == myEventPacketP->event) || (CoordinatorAppList[i].globalAppGroup == appGroup))
        {
            if (CoordinatorAppList[i].globalAppId != 0)
            {
                // suspend/kill this app
                // search new workerNodes/appMaster
                // start new app

                // send update to appMaster
                //coordinatorSendAppMasterPacket(id, CoordinatorAppList[i].reference, CoordinatorAppList[i].globalAppId);

                //last application is done ...
                if ((CoordinatorAppList[i].status == APPLICATION_RUN_FORGET) && (CoordinatorAppList[i].timestamp < ticks))
                {
                    nextEntry = i;
                    i = COORDINATOR_APP_ENTRIES;
                    break;
                }




                coordinatorInternalState |= COORDINATOR_STATE_UPDATE;
                CoordinatorAppList[i].event = myEventPacketP->event;
                CoordinatorAppList[i].globalAppId = getGlobalAppId(myEventPacketP->event);
                CoordinatorAppList[i].status = REQUEST_EVENT;
                CoordinatorAppList[i].timestamp = ticks;
                CoordinatorAppList[i].timeout = ticks + 3000;
                CoordinatorAppList[i].reference = nextEntry;  //TODO: mindless
                CoordinatorAppList[i].globalAppGroup = appGroup;

                updatePacketP->packetType = PACKET_TYPE_APP_UPDATE;
                updatePacketP->application = CoordinatorAppList[i].globalAppId;
                updatePacketP->update = PACKET_SUBTYPE_APP_STOP_DEL_1;
                updatePacketP->dstId = CoordinatorAppList[i].masterId;
                updatePacketP->srcId = myNodeId;
                updatePacketP->payloadsize = sizeof(PACKET_APPLICATION_UPDATE);
                updatePacketP->reference = CoordinatorAppList[i].reference;
                networkSendPacket((GENERIC_PACKET*) updatePacketP);

                break;
            }
            else if ((CoordinatorAppList[i].status == REQUEST_EVENT) || (CoordinatorAppList[i].status == REQUEST_APP))
            {
                //Update is running
                break;
            }
        }
        //find empty slot
        else if ((nextEntry == 0xFF) && (CoordinatorAppList[i].globalAppId == 0))
        {
            nextEntry = i;
        }
    }

    //"i" have now the next free / current entry;
    //TODO: was ist mit "i" wenn UPDATE ???

    if (i >= COORDINATOR_APP_ENTRIES)  //keine laufende App
    {
        // info for manager
        coordinatorInternalState |= COORDINATOR_STATE_REQUEST;

        // Entry in List
        CoordinatorAppList[nextEntry].event = myEventPacketP->event;
        CoordinatorAppList[nextEntry].globalAppId = getGlobalAppId(myEventPacketP->event);
        CoordinatorAppList[nextEntry].status = REQUEST_EVENT;
        CoordinatorAppList[nextEntry].timestamp = ticks;
        CoordinatorAppList[nextEntry].reference = nextEntry;  //TODO: mindless
        CoordinatorAppList[nextEntry].globalAppGroup = appGroup;
        //Generate a request for all other sensornodes and myself

        //check local resources
        p = resourceManagerApplicationRequestLocal(
                appManagerGetLocalAppId(myEventPacketP->event),
                (unsigned int) nextEntry,
                getGlobalAppId(myEventPacketP->event),
                PACKET_SUBTYPE_REQUEST_LOC
                );

        if (p != NULL) //receive the "packet" local
        {
            coordinatorReceiveResponse(p);
        }

        //TODO 1:1 event->app mapping
        coordinatorSendApplicationRequest(myEventPacketP->event, 0x01, nextEntry);

    }
}

void MYCLASS coordinatorSendApplicationRequest(unsigned int application, unsigned int request,
        unsigned int reference)
{
    PACKET_APPLICATION_REQUEST* requestPacketP = (PACKET_APPLICATION_REQUEST*) &txPacketPrepare.genericPacket;
    requestPacketP->srcId = myNodeId;
    requestPacketP->dstId = 0xFFFF;
    requestPacketP->ttl = DEFAULT_TTL;
    requestPacketP->packetType = PACKET_TYPE_NODE_REQUEST;
    requestPacketP->subType = PACKET_SUBTYPE_REQUEST_LOC;  //TODO: Request all
    requestPacketP->payloadsize = sizeof(PACKET_APPLICATION_REQUEST) - HEADERSIZE;
    requestPacketP->application = application;
    requestPacketP->reference = reference;
    requestPacketP->request = request;
    networkSendPacket((GENERIC_PACKET*) requestPacketP);

    clusterApplicationUpdateTimer(TIMER_ID_COORDINATOR_REQUEST_TIMEOUT, TIMER_TYPE_OFFSET, COORDINATOR_REQUEST_TIMEOUT);
    //start timeout-timer
    //COORDINATOR_REQUEST_TIMEOUT
}


void MYCLASS coordinatorReceiveAppMasterResponse(PACKET_APP_MASTER_RESPONSE* responsePacketP)
{
// Search for corresponding entry
    for (int i=0; i<COORDINATOR_APP_ENTRIES;i++ )
    {
        if ((CoordinatorAppList[i].globalAppId == responsePacketP->application) &&
                (CoordinatorAppList[i].reference == responsePacketP->reference))
        {
            if (responsePacketP->response == RESPONSE_OK_AND_FORGET)
            {
                CoordinatorAppList[i].status = APPLICATION_RUN_FORGET;
                CoordinatorAppList[i].timestamp = responsePacketP->expire;  //TODO: Change to a time offset
                break;
            }
            //CoordinatorAppList[i].timestamp = responsePacketP->expire;


        }

    }
        //oordinatorAppList[index].reference
}

void MYCLASS coordinatorReceiveResponse(PACKET_APPLICATION_RESPONSE* responsePacketP)
{
    //TODO: Request->Response
    //search empty place
    unsigned int i, j = 0;
    for (i = 0; i < NODE_ENTRIES; i++)
    {
        if (nodeEntryList[i].reference == IS_EMPTY) //search empty entry
        {
            nodeEntryList[i].reference = responsePacketP->reference;
            nodeEntryList[i].nodeId = responsePacketP->srcId;

            // if first entry is the summary value, use this also
            if ((responsePacketP->payloadsize > 8)
                    && ((responsePacketP->resourceEntry[0].resourceId) == RESOURCE_ID_SUMMARY))
            {
                nodeEntryList[i].resourceEntry[0].value = responsePacketP->resourceEntry[0].value;
                nodeEntryList[i].resourceEntry[0].resourceId = RESOURCE_ID_SUMMARY;
                j++;
            }
            for (; j < MAX_RESOURCE_ENTRIES; j++)
            {
                if (responsePacketP->payloadsize < (j * sizeof(RESOURCE_ENTRY)) + 8)
                {
                    nodeEntryList[i].resourceEntry[j].resourceId = IS_EMPTY;
                    continue;
                }
                nodeEntryList[i].resourceEntry[j].resourceId = responsePacketP->resourceEntry[j].resourceId;
                nodeEntryList[i].resourceEntry[j].value = responsePacketP->resourceEntry[j].value;

                //break if last entry
                //responsePacketP->payloadsize)

            }
            break;
        }
    }
}

unsigned int MYCLASS coordinatorChoiseAppMaster(unsigned int index)
{
    // select the best application master
    unsigned int i;
    volatile int v = 0;
    unsigned short countNodes = 0;
    unsigned short appMaster = 0xFFFF;
    unsigned short maxValue = 0;

    for (i = 0; i < NODE_ENTRIES; i++)
    {
        if (CoordinatorAppList[index].reference == nodeEntryList[i].reference)
        {
            // coordinator known this application
            countNodes++;
            if (nodeEntryList[i].resourceEntry[0].value >= maxValue) //find maximum
            {
                maxValue = nodeEntryList[i].resourceEntry[0].value;
                appMaster = nodeEntryList[i].nodeId;
            }
        }
    }
    //check if we have enough nodes for any possible run

//    switch (CoordinatorAppList[index].appId)
//    {
//        case 1:
//        case 2:
//    }

    //debug
    //appMaster = 5;

    return appMaster;
}

void MYCLASS coordinatorSendAppMasterPacket(unsigned int destId, unsigned int reference,
        unsigned int application)
{
    unsigned int i, cnt = 0; //cnt --> Zähler fur einträge im Packet
    PACKET_APPLICATION_MASTER_REQUEST* requestPacketP =
            (PACKET_APPLICATION_MASTER_REQUEST*) &txPacketPrepare.genericPacket;
    requestPacketP->srcId = myNodeId;
    requestPacketP->dstId = destId;
    requestPacketP->ttl = DEFAULT_TTL;
    requestPacketP->packetType = PACKET_TYPE_APP_MASTER_REQUEST;
    requestPacketP->reference = reference;
    requestPacketP->application = application;

    // TODO: maybe sort ??
    for (i = 0; i < NODE_ENTRIES; i++)
    {
        if ((reference == nodeEntryList[i].reference) && (nodeEntryList[i].reference != IS_EMPTY))
        {
            if (cnt < 10)
            {
                //memcpy(&(*requestPacketP).nodeEntries[cnt++], &nodeEntryList[i], sizeof(NODE_ENTRY));
                requestPacketP->nodeEntries[cnt].nodeId = nodeEntryList[i].nodeId;
                requestPacketP->nodeEntries[cnt].resourceSum = nodeEntryList[i].resourceEntry[0].value;
                requestPacketP->nodeEntries[cnt].resourceId = nodeEntryList[i].resourceEntry[1].resourceId;
                requestPacketP->nodeEntries[cnt].resourceValue = nodeEntryList[i].resourceEntry[1].value;
                cnt++;
            }
            nodeEntryList[i].reference = 0;
        }
    }
    if (cnt != 0)
    {
        requestPacketP->payloadsize = cnt * sizeof(XMIT_NODE_ENTRY) + 8;
        networkSendPacket((GENERIC_PACKET*) requestPacketP);
    }

//  requestPacketP->request = request;
//  networkSendPacket((GENERIC_PACKET*) requestPacketP);
}

//TODO: implement this later into coordinatorManager()
void MYCLASS coordinatorManagerProcessRequest(void)
{
    int i;
    unsigned int id;

    for (i = 0; i < COORDINATOR_APP_ENTRIES; i++) //search relevant event
    {

        if ((coordinatorInternalState & COORDINATOR_STATE_REQUEST) && (CoordinatorAppList[i].status == REQUEST_EVENT)
                && ((CoordinatorAppList[i].timestamp + COORDINATOR_REQUEST_TIMEOUT) <= ticks))
        {
            //found correct entry
            //Timeout !
            id = coordinatorChoiseAppMaster(i);
            //if no application was started...
            coordinatorInternalState &= ~COORDINATOR_STATE_REQUEST;
            //CoordinatorAppList[i].status = REQUEST_DONE;
            //coordinatorSendAppMasterPacket(id, CoordinatorAppList[i].reference, CoordinatorAppList[i].appId);

            if (id==myNodeId && 0)
            {
                volatile int stop=1234;
            }
            else
            {
                //build packet and clear list
                CoordinatorAppList[i].globalAppId = getGlobalAppId(CoordinatorAppList[i].event); //get Application from givin event
                CoordinatorAppList[i].status = 0;
                CoordinatorAppList[i].event = 0;
                CoordinatorAppList[i].masterId = id;
                CoordinatorAppList[i].masterIdAlt = id;
                CoordinatorAppList[i].timestamp = ticks;
                CoordinatorAppList[i].timeout = ticks + 1000; //TODO: Change to defined const value
                CoordinatorAppList[i].status = REQUEST_DONE;

                coordinatorSendAppMasterPacket(id, CoordinatorAppList[i].reference, CoordinatorAppList[i].globalAppId);

                //clear all nodeListEntries
                for (int j = 0; j < NODE_ENTRIES; j++)
                {
                    if (nodeEntryList[j].reference == CoordinatorAppList[i].reference)
                    {
                        nodeEntryList[j].reference = IS_EMPTY;
                    }
                }

                //

                //clear this entry as empty
            }
        }
    }
}

//Manage Apps/AppMasters
// Start/Suspend/Stop a running application
void MYCLASS coordinatorManager(void)
{
    int i, j;
    unsigned int id;
    // just work only with on request at the same time ... --> memory usage for collect informations
    for (i = 0; i < COORDINATOR_APP_ENTRIES; i++)
    {
        //state machine for managing events
        if (coordinatorInternalState & COORDINATOR_STATE_REQUEST)
        {

            if (CoordinatorAppList[i].status == REQUEST_EVENT)
            {
                CoordinatorAppList[i].status = REQUEST_APP;
                CoordinatorAppList[i].timestamp = ticks;

                //Search App-ID
                for (j = 0; j < EVENT_TO_APP_ENTRIES; j++)
                {
                    //Request for nodes, if application known
                    if (CoordinatorAppList[i].event == coordinatorEventMap[j].eventId)
                    {
                        CoordinatorAppList[i].globalAppId = coordinatorEventMap[j].appId;
                        CoordinatorAppList[i].reference = ((CoordinatorAppList[i].timestamp & 0xFFF)
                                + ((i & 0x0F) << 12));

                        /*******************************************
                         * Generate a Broadcast Message for Request *
                         ********************************************/
                        //reference = i + random value !!!
                        coordinatorSendApplicationRequest(CoordinatorAppList[i].globalAppId, 0,
                                CoordinatorAppList[i].reference);
                    }
                }
                //
            }
            else if (CoordinatorAppList[i].status == REQUEST_APP)
            {
                if (ticks > (CoordinatorAppList[i].timestamp + COORDINATOR_REQUEST_TIMEOUT)) // TODO: or we have enough nodes
                {
                    //Timeout !
                    id = coordinatorChoiseAppMaster(CoordinatorAppList[i].reference);
                    //if no application was started...
                    coordinatorInternalState &= ~COORDINATOR_STATE_REQUEST;
                    CoordinatorAppList[i].status = REQUEST_DONE;
                    coordinatorSendAppMasterPacket(id, CoordinatorAppList[i].reference,
                            CoordinatorAppList[i].globalAppId);
                    CoordinatorAppList[i].globalAppId = 0;
                    //build packet and clear list
                }
            }
        }
        else if (coordinatorInternalState & COORDINATOR_STATE_ALIVE)
        {
            if (CoordinatorAppList[i].status == APPLICATION_RUN)
            {
                if (CoordinatorAppList[i].timestamp > ticks)
                {
                    // App is dieing ?
                    // TODO
                }
            }
        }
    }
    return;
}

void MYCLASS coordinatorInit(void)
{
    int i;
    //Clear the List
    for (i = 0; i < COORDINATOR_APP_ENTRIES; i++)
    {
        CoordinatorAppList[i].globalAppId = 0;
        CoordinatorAppList[i].globalAppGroup = 0;
        CoordinatorAppList[i].status = 0;
        CoordinatorAppList[i].event = 0;
    }
    coordinatorInternalState = 0x00;

    for (i = 0; i < NODE_ENTRIES; i++)
    {
        nodeEntryList[i].reference = IS_EMPTY;  //mark this entry as empty
    }
}
