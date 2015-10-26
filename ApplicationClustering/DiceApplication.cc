#include "DiceApplication.h"
#include "BaseMacLayer.h"
#include "NetwControlInfo.h"
//#include "ce-network.h"
#include <omnetpp.h>
#include <WakeUpPacket_m.h>
#include <SimpleBattery.h>
#include <PhyLayerBattery.h>
#include <FindModule.h>
using std::endl;

//Globals

extern GENERIC_PACKET_RX rxPacketWork, rxPacketIsr, rxUartPacket;
extern GENERIC_PACKET_TX txPacket, txPacketPrepare;

Define_Module(DiceApplication)
;

void DiceApplication::initialize(int stage)
{
    BaseModule::initialize(stage);

    if (stage == 0)
    {
        // begin by connecting the gates
        // to allow messages exchange
        dataOut = findGate("lowerLayerOut");
        dataIn = findGate("lowerLayerIn");
        ctrlOut = findGate("lowerControlOut");
        ctrlIn = findGate("lowerControlIn");

        clusterApp = new ClusterApplication(this, dataOut);
        clusterApp->myBaseHost = findHost();
        clusterApp->mySimpleBattery = FindModule<SimpleBattery*>::findSubModule(findHost());
        clusterApp->myPhyLayerBattery = FindModule<PhyLayerBattery*>::findSubModule(findHost());

        //myData = new Data(clusterApp);
        // myNetwork = new Network(myData,this,dataOut);
        //myNetwork = new Network(clusterApp);

        clusterApp->clusterApplicationUpdateTickCounter(0);

        INITIAL_DELAY = 5; // initial delay before sending first packet

        delayTimer = new cMessage("app-delay-timer");
        clusterApp->sleepTimeout = 100;
        clusterApp->myNodeId = LAddress::L3Type(par("nodeAddr").longValue());
        clusterApp->coordinatorNodeId = LAddress::L3Type(par("coordinatorNodeAddr").longValue());

        scheduleAt(simTime() + INITIAL_DELAY + uniform(0, 0.001), delayTimer); // we add a small shift to avoid systematic collisions
    }
    else  if (stage == 1)
    {
        nextDice=0;
        clusterApp->wakeupSleepEnterSleep();
    }
    //for (;;)
    //wait( (simtime_t) 0.001 );

    //myData->myNodeId = LAddress::L3Type( par("nodeAddr").longValue() );

    //diceApplication = this;
}

DiceApplication::~DiceApplication()
{
    if (delayTimer)
        cancelAndDelete(delayTimer);
}

void DiceApplication::finish()
{

}

void DiceApplication::sendPacket(void)
{
    ev<< "DiceApp...Send Packet" << endl;

}
void DiceApplication::setPositions(void)
{
    int pos = 0;
    unsigned char positions[10] = {0,1,2,3,4,5,6,7,8,9};
    unsigned char cnt=0;
    unsigned int posi[10][2] = {
            {100,100}, {200,100},{300,100},
            {100,200}, {200,200},{300,200},
            {100,300}, {200,300},{300,300},
            {450,250}};
    cTopology topo("topo");
    char * pEnd;
    topo.extractByProperty("node");
    cModule *module = clusterApp->myBaseHost;
    cModule *myselfModule = clusterApp->myBaseHost;

    char c = 0;
    if (defPos==1)
    {
        positions[2] = 4;
        positions[4] = 2; //mitte
    }
    else
    {
        //randomice nodes position
        for (unsigned int node=0;node<10;node++)
        {
             int r = (rand() % (10-node)) + node; // 1<-10 ... 1<-1;
             c = positions[r];
             positions[r] = positions[node];
             positions[node] = c;
        }
    }

    //set new node positions

    int myPosX = strtol(module->getDisplayString().getTagArg("p", 0), &pEnd, 10);
    int myPosY = strtol(module->getDisplayString().getTagArg("p", 1), &pEnd, 10);

    //search for other nodes
    //https://groups.google.com/forum/#!msg/omnetpp/uavPHeB-5P8/bMK2_K2o5D4J
    int n = topo.getNumNodes();
    for (int i = 0; i < n; i++)
    {
        cTopology::Node *aNode = topo.getNode(i);
        //ev << "RM-getLocation: module: " << destNode->getModuleId() << endl;
        //destNode->getDistanceToTarget();

        //destNode->getModuleId();
        module = simulation.getModule(aNode->getModuleId());
        if (module!=myselfModule)
        {

            //posi[positions[cnt]][0]  ==


            module->getDisplayString().setTagArg("p", 0, posi[positions[cnt]][0]);
            module->getDisplayString().setTagArg("p", 1, posi[positions[cnt]][1]);
            module->getDisplayString().setTagArg("i2", 0, "status/off");
            //myBaseHost->getDisplayString().setTagArg("i2", 0, "status/red");
            cnt++;
        }
        //int posX = strtol(module->getDisplayString().getTagArg("p", 0), &pEnd, 10);
        //int posY = strtol(module->getDisplayString().getTagArg("p", 1), &pEnd, 10);

    }

}

void DiceApplication::sendDiceEvent(void)
{


    PACKET_EVENT* eventPacketP = (PACKET_EVENT*) &(clusterApp->txPacketPrepare.genericPacket);
    //sprintf(bubblestr,"Dicing: %i",i);
    //getParentModule()->bubble(bubblestr);
    //myBaseModule->getParentModule()->bubble(



    eventPacketP->srcId = clusterApp->myNodeId;
    eventPacketP->dstId = clusterApp->coordinatorNodeId;
    eventPacketP->ttl = DEFAULT_TTL;
    eventPacketP->packetType = PACKET_TYPE_EVENT;
    eventPacketP->payloadsize = sizeof(PACKET_EVENT) - HEADERSIZE;
    eventPacketP->event = nextDice;
    eventPacketP->timestamp = 01234;
    eventPacketP->random = rand() & 0xFFFF;

    clusterApp->networkSendPacket((GENERIC_PACKET*) eventPacketP);
    clusterApp->wakeupSleepUpdateTimer();
    nextDice = 0;
    //networkSendPacketSim((GENERIC_PACKET*) eventPacketP,send,dataOut);

//    if (i % 2 == 0)
//        clusterApp->myBaseHost->getDisplayString().setTagArg("b", 3, "yellow");
//    else
//        clusterApp->myBaseHost->getDisplayString().setTagArg("b", 3, "red");

}

void DiceApplication::handleMessage(cMessage * msg)
{

    //update tick counter
    char bubblestr[16];
    clusterApp->clusterApplicationUpdateTickCounter(simTime().inUnit(-3));

    debugEV << "In DiceApplication::handleMessage" << endl;

    if (msg == clusterApp->sleepTimer)
    {
        clusterApp->wakeupSleepEnterSleep();
    }
    else if (msg == clusterApp->sysTimer)
    {
        clusterApp->clusterApplicationTimerEvent(msg->par("timerId"), msg->par("timerValue"));
        //delete msg;
    }
    else if (msg == delayTimer)
    {
        clusterApp->wakeupSleepLeaveSleep();

        if (nextDice == 0)  //DiceEvent
        {
            INITIAL_DELAY = 30;


            setPositions();
            nextDice = rand() % 6 + 1;
            ev<< "DiceEvent: " << nextDice << endl;
            sprintf(bubblestr,"dice/Dice%ia",nextDice);
            clusterApp->myBaseHost->getDisplayString().setTagArg("i", 0, bubblestr);
            //set labelname to dice
            sprintf(bubblestr,"Dice: %i  ",nextDice);
            clusterApp->myBaseHost->getDisplayString().setTagArg("t", 0, bubblestr);

        }


        if (clusterApp->otherNodesInSleepMode)
        {
            clusterApp->otherNodesInSleepMode = false;
            //Send WakeUp-Packet
            debugEV << "  start wakeup" << endl;
            WakeUpPacket* wuPacketP = new WakeUpPacket();
            wuPacketP->setDestAddr(0xFFFF);
            NetwControlInfo::setControlInfo(wuPacketP, LAddress::L2BROADCAST);
            send(wuPacketP, dataOut);
            //wait some ms
            scheduleAt(simTime() + 0.05 + uniform(0, 0.001), delayTimer);
        }
        else
        {
            sendDiceEvent();
            nextDice = 0;
            debugEV << "  processing application timer." << endl;
            if (!delayTimer->isScheduled())
            {
                scheduleAt(simTime() + INITIAL_DELAY + uniform(0, 0.001), delayTimer);
            }
        }
    }
    else if (msg->getArrivalGateId() == dataIn)
    {

//         // we received a data message from someone else !
        //         ApplPkt* m = dynamic_cast<ApplPkt*>(msg);
//         if (debug)
//             debugEV << "I (" << nodeAddr << ") received a message from node "
//                 << m->getSrcAddr() << " of size " << m->getBitLength() << "." << endl;
//         nbPacketsReceived++;
//
//         if (stats) {
//             simtime_t theLatency = msg->getArrivalTime() - msg->getCreationTime();
//             latencies[m->getSrcAddr()].collect(SIMTIME_DBL(theLatency));
//             testStat.collect(SIMTIME_DBL(theLatency));
//         }
//
//         if (trace) {
//             simtime_t theLatency = msg->getArrivalTime() - msg->getCreationTime();
//             latenciesRaw.record(SIMTIME_DBL(theLatency));
//         }
//
        delete msg;
    }
    else if (msg->getArrivalGateId() == ctrlIn)
    {
//         debugEV << "Received a control message." << endl;
//         // msg announces end of transmission.
//         if (msg->getKind() ==BaseMacLayer::TX_OVER)
//         {
//             isTransmitting = false;
//             if (remainingPackets > 0 && flood && !delayTimer->isScheduled()) {
//                 scheduleAt(simTime() + 0.001*001 + uniform(0, 0.001*0.001), delayTimer);
//             }
//         }
        delete msg;
    }
    else
    {
        // default case
//         if (debug) {
//             ApplPkt* m = static_cast<ApplPkt*>(msg);
//             debugEV << "I (" << nodeAddr << ") received a message from node "
//                     << (static_cast<ApplPkt*>(msg))->getSrcAddr() << " of size " << m->getBitLength() << "." << endl;
//         }
        delete msg;
    }

}
