/*
 * ce-data.cpp
 *
 *  Created on: 28.08.2013
 *      Author: limir
 */

#include "ce-clusterApplication.h"
#include "ModuleAccess.h"
#include <SimpleBattery.h>

void MYCLASS resourceManagerSendRequestResponse(PACKET_APPLICATION_REQUEST* myRequestPacket, unsigned int value)
{
    PACKET_APPLICATION_REQUEST* responsePacketP = (PACKET_APPLICATION_REQUEST*) &txPacket.genericPacket;
    responsePacketP->dstId = coordinatorNodeId;
    responsePacketP->srcId = myNodeId;
    responsePacketP->packetType = PACKET_TYPE_NODE_RESPONSE;
    responsePacketP->ttl = DEFAULT_TTL;
    responsePacketP->subType = myRequestPacket->subType;
    responsePacketP->payloadsize = sizeof(PACKET_APPLICATION_REQUEST) - HEADERSIZE;
    responsePacketP->application = myRequestPacket->application;
    responsePacketP->reference = myRequestPacket->reference;
    responsePacketP->request = myRequestPacket->request;
    responsePacketP->value = value;
    networkSendPacket((GENERIC_PACKET*) responsePacketP);
}

unsigned int MYCLASS resourceManagerGetLocation(void)
{
// TODO only for omnet
    int pos = 0;

    /*

     const double dCapacityRatio = estimateResidualRelative();
     if((dCapacityRatio < 0.8) && (dCapacityRatio > 0.6)) {
     host->getDisplayString().setTagArg("i2",0,"status/battery_80");
     }
     */
    cTopology topo("topo");
    char * pEnd;
    topo.extractByProperty("node");
    cModule *module = myBaseHost;
    int myPosX = strtol(module->getDisplayString().getTagArg("p", 0), &pEnd, 10);
    int myPosY = strtol(module->getDisplayString().getTagArg("p", 1), &pEnd, 10);

    //search for other nodes
    //https://groups.google.com/forum/#!msg/omnetpp/uavPHeB-5P8/bMK2_K2o5D4J
    for (int i = 0; i < topo.getNumNodes(); i++)
    {
        cTopology::Node *destNode = topo.getNode(i);
        //ev << "RM-getLocation: module: " << destNode->getModuleId() << endl;
        //destNode->getDistanceToTarget();

        //destNode->getModuleId();
        module = simulation.getModule(destNode->getModuleId());
        int posX = strtol(module->getDisplayString().getTagArg("p", 0), &pEnd, 10);
        int posY = strtol(module->getDisplayString().getTagArg("p", 1), &pEnd, 10);

        if (((myPosX - posX) < 10) && ((myPosX - posX) > (-10)))        //vertical
        {
            if (((myPosY - posY) < 110) && ((myPosY - posY) > 90))
                pos += 1;     // top
            if (((myPosY - posY) < (-90)) && ((myPosY - posY) > (-110)))
                pos += 2;     // bottom
        }
        if (((myPosY - posY) < 10) && ((myPosY - posY) > (-10))) //horizontal
        {
            if (((myPosX - posX) < 110) && ((myPosX - posX) > 90))
                pos += 4;     // left
            if (((myPosX - posX) < (-90)) && ((myPosX - posX) > (-110)))
                pos += 8;     // right
        }
    }

    //return the absolute position

    switch (pos)
    {
        case 10:
            return 1;
        case 14:
            return 2;
        case 6:
            return 3;
        case 11:
            return 4;
        case 15:
            return 5;
        case 7:
            return 6;
        case 9:
            return 7;
        case 13:
            return 8;
        case 5:
            return 9;
        default:
            return 0;
    }
}

void MYCLASS resourceManagerSendResponsePacket(PACKET_RESOURCE_REQUEST* myRequestPacket, unsigned int value)
{
    PACKET_RESOURCE_RESPONSE* dataPacketP = (PACKET_RESOURCE_RESPONSE*) &txPacketPrepare.genericPacket;
    dataPacketP->dstId = myRequestPacket->masterId;
    dataPacketP->srcId = myNodeId;
    dataPacketP->packetType = PACKET_TYPE_RESOURCE_RESPONSE;
    dataPacketP->subType = 0;
    dataPacketP->value = value;
    dataPacketP->application = myRequestPacket->application;
    dataPacketP->reference = myRequestPacket->reference;

    //TODO //only UART

    //queueInsertObjectSpecial(&txUartQueue,dataPacketP,sizeof(PACKET_APPLICATION_RESPONSE));

    //networkSendPacketDirect(GENERIC_PACKET* myPacket,unsigned short destinationNode);
    return;
}

void MYCLASS resourceManagerInit(void)
{

    resourcesLocation = UNKNOWN;
    resourcesHardwareUsed = 0;
    resourcesHardwareFree = 0xFFFF;

}

void MYCLASS resourceManagerCheck(void)
{

}

unsigned int MYCLASS resourceManagerCheckHardware(unsigned int appId, unsigned char* resourcePos)
{
    unsigned int i = RESOURCE_MAP_ENTRIES;
    for (i = 0; i < RESOURCE_MAP_ENTRIES; i++)
    {
        if (resourceMap[i].appId == appId)
        {
            *resourcePos = i;
            //Check Resources
            if ((resourceMap[i].resourcesNeed & resourcesHardwareFree) == resourceMap[i].resourcesNeed)
                return 2;     // Resource is not used...
            return 1;     // Resource is in use
        }
    }
    return 0;  // Application not executable at this node
}

unsigned int MYCLASS resourceManagerCheckCpuUsage(unsigned int appId, unsigned char* resourcePos)
{
    return 1;
    //TODO
}

unsigned int MYCLASS resourceManagerReservation(unsigned int appId, unsigned int masterId, unsigned int timeout)
{
    unsigned int id;
    /*
     id = appschedulerInsertAppEntry(
     appId,
     APP_STATE_RESERVED,        // Reservation
     masterId, //myApplicationPacket->srcId,
     1,  //count,
     0, //delay,
     0, //myApplicationPacket->timeout,
     0, //myApplicationPacket->parameterA,
     0, //myApplicationPacket->parameterB,
     0  //myApplicationPacket->options
     );
     */
    return 0;
}

unsigned int MYCLASS resourceManagerCheckEnergyStatus(unsigned int appId, unsigned char* resourcePos)
{
    //TODO
#ifdef MYCLASS //Simu    int energy = (int) (mySimpleBattery->estimateResidualRelative() * 256);    if (energy > 255)    energy = 255;    return energy;#endif
    return 0xFFFF;
}

PACKET_APPLICATION_RESPONSE* MYCLASS resourceManagerApplicationRequestLocal(unsigned int localApplication,
        unsigned int reference, unsigned int globalApplication, unsigned char option)
{
    // this is a global requst for execute an application
    // return a reaponse only if execution is possible (anyway)

    unsigned int summary;
    PACKET_APPLICATION_RESPONSE* myResponsePacket = (PACKET_APPLICATION_RESPONSE*) &txPacket.genericPacket;
    unsigned char c_dummy;
    unsigned short s_dummy = 0;

    const char appLocMat[7][10] = {
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

    summary = resourceManagerCheckHardware(localApplication, &c_dummy);

    if (summary == 0) // no answer if hardware is not matching
        return NULL;

    myResponsePacket->resourceEntry[1].resourceId = RESOURCE_ID_LOCATION;
    c_dummy = resourceManagerGetLocation();

    if ((globalApplication < 7) && (c_dummy < 10))
    {
        s_dummy = (appLocMat[globalApplication][c_dummy] << 4);
        s_dummy |= c_dummy;
    }

    // TODO: // no answer if wrong position
    if (((s_dummy & 0xF0) == 0) && (option == PACKET_SUBTYPE_REQUEST_LOC))
        return NULL;

    myResponsePacket->resourceEntry[1].value = s_dummy;

    myResponsePacket->resourceEntry[2].resourceId = RESOURCE_ID_HARDWARE;
    myResponsePacket->resourceEntry[2].value = summary;
    summary <<= 8;

    //check if location is good or bad
    //s_dummy = resourceManagerCheckLocation(myRequestPacket->application,s_dummy);
    //answer 0=>bad 1=>group1 2=>group2 3=>group1+2
    c_dummy = 0;

    c_dummy = resourceManagerCheckEnergyStatus(localApplication, &c_dummy);
    summary += c_dummy;
    myResponsePacket->resourceEntry[3].resourceId = RESOURCE_ID_ENERGY;
    myResponsePacket->resourceEntry[3].value = c_dummy;

    myResponsePacket->resourceEntry[4].resourceId = RESOURCE_ID_CPU;
    myResponsePacket->resourceEntry[4].value = resourceManagerCheckCpuUsage(localApplication, &c_dummy);

    myResponsePacket->resourceEntry[0].resourceId = RESOURCE_ID_SUMMARY;
    myResponsePacket->resourceEntry[0].value = summary;

    //header
    myResponsePacket->dstId = coordinatorNodeId;
    myResponsePacket->srcId = myNodeId;
    myResponsePacket->packetType = PACKET_TYPE_NODE_RESPONSE;
    myResponsePacket->ttl = DEFAULT_TTL;
    myResponsePacket->subType = 0;
    myResponsePacket->payloadsize = (5 * sizeof(RESOURCE_ENTRY)) + 8;    //TODO: 5 --> is not static

    myResponsePacket->response = RESPONSE_OK_VALUE;
    myResponsePacket->appId = 0;    // TODO: local appId

    //TODO: Referenz local or from coordinator ???
    myResponsePacket->reference = reference;

    return myResponsePacket;
}

void MYCLASS resourceManagerApplicationRequest(PACKET_APPLICATION_REQUEST* myRequestPacket)
{
    PACKET_APPLICATION_RESPONSE* myResponsePacket;
    myResponsePacket = resourceManagerApplicationRequestLocal(

            //Use local applicationId for a requested local app
            appManagerGetLocalAppId(myRequestPacket->application), myRequestPacket->reference,
            myRequestPacket->application, myRequestPacket->subType);

    if (myResponsePacket != NULL)
        networkSendPacket((GENERIC_PACKET*) myResponsePacket);
}

#if 0
void MYCLASS resourceManagerApplicationRequest(PACKET_APPLICATION_REQUEST* myRequestPacket)
{
    // this is a global requst for execute an application
    // return a reaponse only if execution is possible (anyway)

    unsigned int summary;
    PACKET_APPLICATION_RESPONSE* myResponsePacket = (PACKET_APPLICATION_RESPONSE*) &txPacket.genericPacket;
    unsigned char c_dummy;
    unsigned short s_dummy=0;

    const char appLocMat[7][10] =
    {
        //pos 0 -->
//                0  1  2  3  4  5  6  7  8  9
        {   0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //0
        {   0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, //1
        {   0, 2, 0, 1, 0, 0, 0, 1, 0, 2}, //2
        {   0, 2, 0, 1, 0, 3, 0, 1, 0, 2}, //3
        {   0, 1, 0, 1, 0, 0, 0, 1, 0, 1}, //4
        {   0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, //5
        {   0, 3, 2, 3, 1, 0, 1, 3, 2, 3}  //6
    };

    summary = resourceManagerCheckHardware(myRequestPacket->application, &c_dummy);

    if (summary == 0) // no answer if hardware is not matching
    return;

    myResponsePacket->resourceEntry[1].resourceId = RESOURCE_ID_LOCATION;
    c_dummy = resourceManagerGetLocation();

    if ((myRequestPacket->application<7) && (c_dummy<10))
    {
        s_dummy = (appLocMat[myRequestPacket->application][c_dummy] << 8);
        s_dummy |= c_dummy;
    }
    myResponsePacket->resourceEntry[1].value = s_dummy;

    myResponsePacket->resourceEntry[2].resourceId = RESOURCE_ID_HARDWARE;
    myResponsePacket->resourceEntry[2].value = summary;
    summary <<= 8;

    //check if location is good or bad
    //s_dummy = resourceManagerCheckLocation(myRequestPacket->application,s_dummy);
    //answer 0=>bad 1=>group1 2=>group2 3=>group1+2
    c_dummy = 0;

    c_dummy = resourceManagerCheckEnergyStatus(myRequestPacket->application, &c_dummy);
    summary += c_dummy;
    myResponsePacket->resourceEntry[3].resourceId = RESOURCE_ID_ENERGY;
    myResponsePacket->resourceEntry[3].value = c_dummy;

    myResponsePacket->resourceEntry[4].resourceId = RESOURCE_ID_CPU;
    myResponsePacket->resourceEntry[4].value = resourceManagerCheckCpuUsage(myRequestPacket->application, &c_dummy);

    myResponsePacket->resourceEntry[0].resourceId = RESOURCE_ID_SUMMARY;
    myResponsePacket->resourceEntry[0].value = summary;

    //header
    myResponsePacket->dstId = coordinatorNodeId;
    myResponsePacket->srcId = myNodeId;
    myResponsePacket->packetType = PACKET_TYPE_NODE_RESPONSE;
    myResponsePacket->ttl = DEFAULT_TTL;
    myResponsePacket->subType = 0;
    myResponsePacket->payloadsize = (5 * sizeof(RESOURCE_ENTRY)) + 8;//TODO: 5 --> is not static

    myResponsePacket->response = RESPONSE_OK_VALUE;
    myResponsePacket->appId = 0;// TODO: local appId

    //TODO: Referenz local or from coordinator ???
    myResponsePacket->reference = myRequestPacket->reference;

    networkSendPacket((GENERIC_PACKET*) myResponsePacket);

    /*
     hardwareValue = resourceManagerCheckHardware(myRequestPacket->application, &dummy);
     location = resourceManagerGetLocation();
     if (hardwareValue != 0)
     {
     cpuValue = resourceManagerCheckCpuUsage(myRequestPacket->application,&dummy);

     }
     // Response to the coordinator node
     // resourceManagerSendResponse

     resourceManagerSendRequestResponse(myRequestPacket, (hardwareValue<<8) + cpuValue);

     return;
     // Check if this application is executable on this node
     */

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
#endif

void MYCLASS resourceManagerRequest(PACKET_RESOURCE_REQUEST* myRequestPacket)
{
    // this is an explicit question for this node
    // search all resources for an given application
    // and answer this request

    //dummy TODO

#if 0
    unsigned int summary;
    PACKET_APPLICATION_RESPONSE* responsePacketP = (PACKET_APPLICATION_RESPONSE*) &txPacket.genericPacket;
    unsigned char dummy;

    summary = resourceManagerCheckHardware(myRequestPacket->application, &dummy);

    if (summary == 0) // no answer if hardware is not matching
    {
        return;
    }

    myResponsePacket->resourceEntry[0].resourceId = RESOURCE_ID_SUMMARY;
    myResponsePacket->resourceEntry[0].value = (summary<<8);

    myResponsePacket->resourceEntry[1].resourceId = RESOURCE_ID_HARDWARE;
    myResponsePacket->resourceEntry[1].value = summary;

    myResponsePacket->resourceEntry[2].resourceId = RESOURCE_ID_CPU;
    myResponsePacket->resourceEntry[2].value =
    resourceManagerCheckCpuUsage(myRequestPacket->application,&dummy);

    myResponsePacket->resourceEntry[3].resourceId = RESOURCE_ID_LOCATION;
    myResponsePacket->resourceEntry[3].value = resourceManagerGetLocation();

#endif
#if 0
    unsigned int hardwareValue,cpuValue;
    unsigned char resourcePos;
    volatile int cnt = (myRequestPacket->payloadsize)-8;
    if (cnt<0)
    return;

    //Check for a possible execution of this app

    //TODO find local appid

    //resourcePos:
    hardwareValue = resourceManagerCheckHardware(myRequestPacket->application, &resourcePos);
    if (hardwareValue==0)
    {   //Response => Execution impossible
        resourceManagerSendResponsePacket(myRequestPacket,RESPONSE_NO_APPLICATON);
        return;
    }
    else if (hardwareValue==1)
    {
        //Fail: Hardware in use
        resourceManagerSendResponsePacket(myRequestPacket,RESPONSE_HARDWARE_IN_USE);
        return;
    }

    //Success / Possible execution of this application
    cpuValue = resourceManagerCheckCpuUsage(myRequestPacket->application,&resourcePos);

    // calculate weight value
    // if this is not zero: reserve slot for app

    // Send also the correct "slot-id" for this reservation
    // set timeout-value
    resourceManagerSendResponsePacket(myRequestPacket,RESPONSE_OK_VALUE);
    // for each resource entry make a data collection

    resourceManagerReservation(
            myRequestPacket->application,
            myRequestPacket->masterId ,
            ticks + RESERVATION_TIMEOUT
    );

    // Reservation of resources and application slot
#endif
}

unsigned int MYCLASS resourceManagerAllocate(APP_STRUCT* myAppStruct)
{
    unsigned char id;
    unsigned int value = 0;
    value = resourceManagerCheckHardware(myAppStruct->appId, &id);
    if (value == 2)
    {
        // unique resources
        //if ((resourceMap[i].resourcesNeed & resourcesHardwareFree) == resourceMap[i].resourcesNeed)
        //resourcesHardwareUsed |= resourceMap[id].resourcesUnique;
        resourcesHardwareFree &= ~(resourceMap[id].resourcesUnique);
    }
    //myAppStruct
    return value;
}

void MYCLASS resourceManagerFree(APP_STRUCT* myAppStruct)
{
    unsigned char id;
    unsigned int value;
    value = resourceManagerCheckHardware(myAppStruct->appId, &id);
    if (value != 0)
        resourcesHardwareFree |= (resourceMap[id].resourcesUnique);

}

