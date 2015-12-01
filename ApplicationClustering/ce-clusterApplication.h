/*
 * ce-data.h
 *
 *  Created on: 28.08.2013
 *      Author: limir
 */

#ifndef CE_CLUSTERAPPLICATION_H_
#define CE_CLUSTERAPPLICATION_H_

#include "ce-packetstructs.h"
#include "ce-appstructs.h"
//#include "ce-data.h"
#include "ce-resourcemanager.h"
#include "ce-appscheduler.h"
#include "ce-coordinator.h"

#include "BaseModule.h"
#include "PhyLayer.h"

#define SLEEP_TIMEOUT 1000
#define MYCLASS ClusterApplication::

class SimpleBattery;
class PhyLayerBattery;
class ClusterApplication
{

    public:
        //Data* myData;
        BaseModule* myBaseModule;
        cModule* myBaseHost;
        int myOutGate;
        bool nodeIsDown = false;
        SimpleBattery* mySimpleBattery;
        PhyLayer* myPhyLayerBattery;
        int mySimpleBatteryId;
        unsigned long ticks;  // internal tick-timer  (ca. 1ms)
        cMessage* sysTimer;

        unsigned long clusterApplicationEvents;

        ClusterApplication(BaseModule* baseModule, int oGate);
        virtual ~ClusterApplication();
        ClusterApplication& operator=(const ClusterApplication&);

        //WakeupSlepp
        int sleepTimeout;
        cMessage* sleepTimer;
        bool sleepAllowed = true;
        bool isInSleepMode = false;
        bool otherNodesInSleepMode = false;

        //from data.c/.h
        unsigned short myNodeId;
        unsigned short myPanId;
        unsigned short coordinatorNodeId = 3;
        GENERIC_PACKET_RX rxPacketWork;
        GENERIC_PACKET_TX txPacket, txPacketPrepare;

        //from reourceManager
        //cpu
        unsigned int resourcesCpuLoadValue;
        //energy
        unsigned int resourcesEnergyReserve;
        unsigned int resourcesEnergyProduction;
        unsigned int resourcesEnergyConsumption;
        //hardware
        unsigned int resourcesHardwareUsed; // [10];   Bitmask
        unsigned int resourcesHardwareFree; // [10];
        //location
        unsigned int resourcesLocation;

        const RESOURCE_MAP_ENTRY resourceMap[RESOURCE_MAP_ENTRIES] = { { LED1_EIN, LED1E, LED1E, 50, 0, 0, 1 }, {
                LED1_AUS, LED1A, LED1A, 0, 0, 0, 1 }, { LED2_EIN, LED2E, LED2E, 50, 0, 0, 1 }, {
                LED2_AUS, LED2A, LED2A, 0, 0, 0, 1 }, { LED3_EIN, LED3E, LED3E, 50, 0, 0, 1 }, {
                LED3_AUS, LED3A, LED3A, 0, 0, 0, 1 }, { LED4_EIN, LED4E, LED4E, 50, 0, 0, 1 }, {
                LED4_AUS, LED4A, LED4A, 0, 0, 0, 1 }, { META_LED1_FLASH, LED1E | LED1A, LED1E | LED1A, 0, 1, 0, 5 }, {
                META_LED2_FLASH, LED2E | LED2A, LED2E | LED2A, 0, 1, 0, 5 }, { META_LED3_FLASH, LED3E | LED3A, LED3E
                | LED3A, 0, 1, 0, 5 }, { META_LED4_FLASH, LED4E | LED4A, LED4E | LED4A, 0, 1, 0, 5 }, { 107, LED1E
                | LED1A, LED1E | LED1A, 0, 1, 0, 5 },

        };

        //Coordinator
        const EVENT_TO_APP_ENTRY coordinatorEventMap[EVENT_TO_APP_ENTRIES] = { { DIE_EVENT_1, 101, 0, 0 }, {
        DIE_EVENT_2, 102, 0, 0 }, { DIE_EVENT_3, 103, 0, 0 }, { DIE_EVENT_4, 104, 0, 0 }, {
        DIE_EVENT_5, 105, 0, 0 }, { DIE_EVENT_6, 106, 0, 0 },

        { KEY_EVENT_1, 107, 0, 0 }, { KEY_EVENT_2, 108, 0, 0 }, };

        unsigned char coordinatorInternalState = 0x00;
        NODE_ENTRY nodeEntryList[NODE_ENTRIES];
        COORDINATOR_APP_ENTRY CoordinatorAppList[COORDINATOR_APP_ENTRIES];

        unsigned int globalEvents = 0;

        //AppScheduler
        APP_STRUCT appList[APP_LISTCOUNT];
        APP_STRUCT* appFirstEntry = NULL;
        APP_STRUCT* appNextEntry = NULL;

        enum TIMER_ID
        {
            TIMER_ID_NONE = 0,
            TIMER_ID_COORDINATOR_REQUEST_TIMEOUT,
            TIMER_ID_COORDINATOR_UPDATE_TIMEOUT,
            TIMER_ID_APPLICATION_SCHEDULER,
            //TIMER_ID_WAKEUP_SLEEP_TIMER
            TIMER_ID_MAX  //last dummy value... for counting only
        };

        enum TIMER_TYPE
        {
            TIMER_TYPE_DELETE = 0, TIMER_TYPE_SET, TIMER_TYPE_OFFSET, TIMER_TYPE_ADD
        //TIMER_TYPE_MAX  //last dummy value... for counting only
        };

    private:
        unsigned long timers[TIMER_ID_MAX];
        unsigned long lastTimerEvent;

    protected:

    public:
        //
        void clusterApplicationUpdateTimer(unsigned char timerId, unsigned char type, unsigned int value);
        void clusterApplicationUpdateTickCounter(unsigned long value);
        void clusterApplicationRefreshTimerEvent(void);
        void clusterApplicationCancelTimers(void);
        void clusterApplicationTimerEvent(unsigned int timerId, unsigned long timerValue);

        //Sleep/Wakeup
        void wakeupSleepEnterSleep(void);
        void wakeupSleepLeaveSleep(void);
        void wakeupSleepInit(void);
        void wakeupSleepUpdateTimer(void);

        //ce-network
        void networkSendPacketDirect(GENERIC_PACKET* myPacket, unsigned short destinationNode);
        void networkSendPacket(GENERIC_PACKET* myPacket);

        //ce-packets
        void packetsProcessMyPacket(GENERIC_PACKET * myPacket);
        void packetsProcessIncommingPacket(GENERIC_PACKET_RX * myPacket);

        //resourceManager
        void resourceManagerInit(void);
        void resourceManagerCheck(void);
        unsigned int resourceManagerAllocate(APP_STRUCT* myAppStruct);
        void resourceManagerFree(APP_STRUCT* myAppStruct);
        void resourceManagerRequest(PACKET_RESOURCE_REQUEST* myRequestPacket);
        void resourceManagerApplicationRequest(PACKET_APPLICATION_REQUEST* myRequestPacket);
        void resourceManagerLocalRequest(unsigned int application);
        PACKET_APPLICATION_RESPONSE* resourceManagerApplicationRequestLocal(unsigned int localApplication,
                unsigned int reference, unsigned int globalApplication, unsigned char option);
        void resourceManagerSendRequestResponse(PACKET_APPLICATION_REQUEST* myRequestPacket, unsigned int value);
        void resourceManagerSendResponsePacket(PACKET_RESOURCE_REQUEST* myRequestPacket, unsigned int value);
        unsigned int resourceManagerCheckHardware(unsigned int appId, unsigned char* resourcePos);
        unsigned int resourceManagerCheckCpuUsage(unsigned int appId, unsigned char* resourcePos);
        unsigned int resourceManagerReservation(unsigned int appId, unsigned int masterId, unsigned int timeout);
        unsigned int resourceManagerCheckEnergyStatus(unsigned int appId, unsigned char* resourcePos);
        /** @brief returns a value for physical location*/
        unsigned int resourceManagerGetLocation(void);

        //coordinator
        unsigned int coordinatorChoiseAppMaster(unsigned int reference);
        void coordinatorReceiveEvent(PACKET_EVENT* myEventPacketP);
        void coordinatorReceiveAppMasterResponse(PACKET_APP_MASTER_RESPONSE* responsePacketP);
        void coordinatorReceiveResponse(PACKET_APPLICATION_RESPONSE* responsePacketP);
        void coordinatorSendApplicationRequest(unsigned int application, unsigned int request, unsigned int reference);
        void coordinatorSendAppMasterPacket(unsigned int destId, unsigned int reference, unsigned int application);
        void coordinatorManagerProcessRequest(void);
        void coordinatorManager(void);
        void coordinatorInit(void);

        //application
        void ApplicationCheckNeighbours(APP_STRUCT* myAppStruct);
        void applicationExecute(APP_STRUCT* myAppStruct);
        void applicationLedSwitch(unsigned int x, unsigned int y);

        //Application Manager
        void appManagerInit(void);
        void appManagerReorg(void);
        void appManagerCheck(void);
        void appManagerApplicationUpdate(PACKET_APPLICATION_UPDATE* myApplicationPacket);
        void appManagerApplicationRequest(PACKET_APPLICATION_REQUEST* myRequestPacket);
        void appManagerApplicationRequestFromNet(PACKET_APPLICATION* myApplicationPacket);
        unsigned int appManagerGetLocalAppId(unsigned int globalAppId);
        void appManagerSendResponse(unsigned int id, unsigned int destination, unsigned int ref,
                unsigned char response);
        void appManagerStartApplicationFromNet(PACKET_APPLICATION* myApplicationPacket);

        //Application Scheduler
        unsigned int appschedulerInsertAppEntry(unsigned char appId, unsigned char status, unsigned int master,
                unsigned char count, unsigned long delay, unsigned long start, unsigned int parameterA,
                unsigned int parameterB, unsigned char options);

        void appschedulerUpdateApp(APP_STRUCT* myAppStruct);
        void appschedulerUpdateFirstApp(void);
        void appschedulerRemoveApp(APP_STRUCT* myAppStruct);
        void appschedulerCalcNextExecution(APP_STRUCT* myAppStruct);
        void appschedulerInsertPosition(APP_STRUCT* myAppStruct);
        void appschedulerInit(void);

        //Application Master
        void appMasterInit(void);
        void appMasterReceiveRequestFromNet(PACKET_APPLICATION_MASTER_REQUEST* myEventPacket);
        unsigned int appMasterReceiveEventFromNet(PACKET_APPLICATION_MASTER_EVENT* myEventPacket);
        void appMasterReceiveEventFromLocale(void);
        unsigned char appMasterChoiceNodes(unsigned int applicationId, PACKET_APPLICATION_MASTER_REQUEST* myEventPacket,
                unsigned int nodes[]);
        void appMasterFirstClassReceiveEventFromNet(PACKET_APPLICATION_MASTER_1ST_EVENT* myEventPacket);   // 0x57
        void appMasterFirstClassReceiveEventFromLocale(void);
        void appMasterReceiveResponse(void);
        void appMasterRequestMaster(unsigned int event, unsigned int destination, unsigned int response);

};

#endif /* CE_CLUSTERAPPLICATION_H_ */
