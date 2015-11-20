#include "MatrixApplication.h"
#include "BaseMacLayer.h"
#include "NetwControlInfo.h"
#include "ce-packets.h"
#include <omnetpp.h>
#include "GenericPacket_m.h"
#include "ce-clusterApplication.h"
#include "FindModule.h"
#include <SimpleBattery.h>
#include <PhyLayerBattery.h>
#include <WakeUpPacket_m.h>
#include "WakeupPhyUtils.h"

using std::endl;

//Globals
extern GENERIC_PACKET_RX rxPacketWork, rxPacketIsr, rxUartPacket;
extern GENERIC_PACKET_TX txPacket, txPacketPrepare;

Define_Module(MatrixApplication);

void MatrixApplication::initialize(int stage)
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

        INITIAL_DELAY = 5; // initial delay before sending first packet

        delayTimer = new cMessage("app-delay-timer");
        scheduleAt(simTime() + INITIAL_DELAY + uniform(0, 0.001), delayTimer); // we add a small shift to avoid systematic collisions

        clusterApp->myNodeId = LAddress::L3Type(par("nodeAddr").longValue());
        clusterApp->coordinatorNodeId = LAddress::L3Type(par("coordinatorNodeAddr").longValue());
    }
    else if (stage ==1)
    {
        int i = clusterApp->myNodeId+1;
        clusterApp->mySimpleBatteryId = clusterApp->mySimpleBattery->registerDevice("Sensornode", 2);  // Sensor + CPU
        clusterApp->wakeupSleepEnterSleep();
    }

}

MatrixApplication::~MatrixApplication()
{
    if (delayTimer)
        cancelAndDelete(delayTimer);
}

void MatrixApplication::finish()
{

}

void MatrixApplication::matrixEvent(void)
{

    //new Package

}

void MatrixApplication::handleMessage(cMessage * msg)
{
    char bubblestr[16];
    double energy = clusterApp->mySimpleBattery->estimateResidualRelative() * 100;
    if (clusterApp->nodeIsDown)
    {
        delete msg;
        return;
    }
    if (energy<5 && !clusterApp->nodeIsDown)
    {
        //kill all timer
        clusterApp->clusterApplicationCancelTimers();
        if (delayTimer->isScheduled())
            cancelEvent(delayTimer);

        //kill all app  //Workaround
        clusterApp->applicationLedSwitch(4,0);
        //disable recv
        clusterApp->nodeIsDown = true;
        clusterApp->myPhyLayerBattery->setRadioState(WakeupMiximRadio::POWERDOWN);
        sprintf(bubblestr," OFF ");
        clusterApp->myBaseHost->getDisplayString().setTagArg("t", 0, bubblestr);
        clusterApp->myBaseHost->getDisplayString().setTagArg("b", 3, "gray");

        delete msg;
        return;

    }

    clusterApp->clusterApplicationUpdateTickCounter(simTime().inUnit(-3));

    //ev<< "Battery State: " << m << endl;
    ev<< "In MatrixApplication::handleMessage" << endl;
    //HostState::setstate(HostState::S)

    int stop = msg->getArrivalGateId() * 100;
    sprintf(bubblestr," %-.2f %% ", energy);
    clusterApp->myBaseHost->getDisplayString().setTagArg("t", 0, bubblestr);
//    if (clusterApp->myNodeId == 3 )
//    {
//        stop = msg->isSelfMessage();
//        stop = 0;
//        GenericPacket* m = dynamic_cast<GenericPacket*>(msg);
//
//    }
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
        matrixEvent();
        ev << "  processing application timer." << endl;
        if (!delayTimer->isScheduled())
        {
            scheduleAt(simTime() + INITIAL_DELAY + uniform(0, 0.001), delayTimer);
        }
    }
    else if ((msg->getArrivalGateId() == dataIn) || (msg->isSelfMessage()==1))
    {
        clusterApp->wakeupSleepUpdateTimer();
//         // we received a data message from someone else !
        WakeUpPacket* w =  dynamic_cast<WakeUpPacket*>(msg);
        if (w!=0)
        {
            if (clusterApp->isInSleepMode) clusterApp->wakeupSleepLeaveSleep();
        }
        GenericPacket* m = dynamic_cast<GenericPacket*>(msg);
        if (m!=0)
        {
            if (((m->getSrcId() != clusterApp->myNodeId) || (m->getDstId() != clusterApp->myNodeId)) && (msg->isSelfMessage()==1))
            {

            }
            else
            {
                ev<< "I (" << clusterApp->myNodeId << ") received a message from node "  << m->getSrcId() << "." << endl;

        //        if (debug)
        //            ev<< "I (" << nodeAddr << ") received a message from node "
        //            << m->getSrcId() << " of size " << m->getBitLength() << "." << endl;
                //getParentModule()->bubble("Packet arrived!");

                clusterApp->rxPacketWork.genericPacket.ttl = m->getTtl();
                clusterApp->rxPacketWork.genericPacket.packetType = m->getPacketType();
                clusterApp->rxPacketWork.genericPacket.subType = m->getSubType();
                clusterApp->rxPacketWork.genericPacket.payloadsize = m->getPayloadsize();
                clusterApp->rxPacketWork.genericPacket.dstId = m->getDstId();
                clusterApp->rxPacketWork.genericPacket.srcId = m->getSrcId();
                for (int i = 0; i < clusterApp->rxPacketWork.genericPacket.payloadsize; i++)
                {
                    clusterApp->rxPacketWork.genericPacket.data[i] = m->getData(i);
                }
                //rxPacketWork.rxRssi = m->

                clusterApp->packetsProcessIncommingPacket(&clusterApp->rxPacketWork);


            }
        }
        delete msg;
    }
    else if (msg->getArrivalGateId() == ctrlIn)
    {

        delete msg;
    }
    else
    {
        delete msg;
    }
}

void MatrixApplication::matrixApplicationMain(void)
{
    //event-fsm

}
