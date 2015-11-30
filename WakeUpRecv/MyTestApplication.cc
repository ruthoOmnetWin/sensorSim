#include "MyTestApplication.h"
#include "BaseMacLayer.h"
#include "NetwControlInfo.h"
#include <omnetpp.h>
#include "GenericPacket_m.h"
#include "FindModule.h"
#include "WakeupPhyUtils.h"
#include "ApplPkt_m.h"
#include "WiseRoutePkt_m.h"

using std::endl;

//Globals

Define_Module(MyTestApplication);




void MyTestApplication::initialize(int stage)
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

        active = true;

        //myApp->myBaseHost = findHost();

        initiatorAddr = par("coordinatorNodeAddr").longValue();
        myNodeId = LAddress::L3Type(par("nodeAddr").longValue());

        //mySimpleBattery = new SimpleBattery();
        mySimpleBattery = FindModule<SimpleBattery*>::findSubModule(findHost());

        //myPhyLayerBattery = new PhyLayerBattery();
        myPhyLayerBattery = FindModule<WakeupPhyLayerBattery*>::findSubModule(findHost());
        //HostState::set

        INITIAL_DELAY = rand() % 5 + 1; // initial delay before sending first packet

        delayTimer = new cMessage("app-delay-timer");
        scheduleAt(simTime() + INITIAL_DELAY + uniform(0, 0.001), delayTimer); // we add a small shift to avoid systematic collisions
    }
    else if (stage ==1)
    {
        mySimpleBatteryId = mySimpleBattery->registerDevice("Sensornode", 2);  // Sensor + CPU
    }

}

MyTestApplication::~MyTestApplication()
{
    if (delayTimer)
        cancelAndDelete(delayTimer);
}

void MyTestApplication::finish()
{

}

void MyTestApplication::sendPacket(void)
{
    if (active) {
        char bubblestr[32];
        if (myNodeId == initiatorAddr)
        {
            ApplPkt* gPacketP = new ApplPkt();
            gPacketP->setDestAddr(LAddress::L3BROADCAST);
            NetwControlInfo::setControlInfo(gPacketP, LAddress::L3BROADCAST);
            send(gPacketP, dataOut);
            //findHost()->sendDelayed(gPacketP, delay, myOutGate);
            return;
        }
        else
        {
    #if 0
            if (sleepState == 0)
            {
                sleepState=1;
                ev<< "Node: " << myNodeId << ": " <<  "Enter SleepMode" << endl;
                myPhyLayerBattery->setRadioState(WakeupMiximRadio::SLEEP);
                findHost()->getDisplayString().setTagArg("i2", 0, "status/red");
            }
            else
            {
                sleepState=0;
                ev<< "Node: " << myNodeId << ": " << "Leave SleepMode" << endl;
                myPhyLayerBattery->setRadioState(WakeupMiximRadio::RX);
                findHost()->getDisplayString().setTagArg("i2", 0, "status/green");
            }
    #endif
        }
    //ev<< "TestApp...Send Packet" << endl;
    //GenericPacket* gPacketP = new GenericPacket();
    //gPacketP->setDstId(LAddress::L2BROADCAST);
    //NetwControlInfo::setControlInfo(gPacketP, LAddress::L2BROADCAST);
    //send(gPacketP, dataOut);
    //findHost()->sendDelayed(gPacketP, delay, myOutGate);
    }

}


void MyTestApplication::handleMessage(cMessage * msg)
{

    //debugEV << "In TestApplication::handleMessage" << endl;
    //char bubblestr[16];
    //double energy = mySimpleBattery->estimateResidualRelative() * 100;
    //sprintf(bubblestr," %i %% ",(int) energy);
    //ev<< "Node: " << myNodeId << ": " << "Battery State: " << bubblestr << endl;
    //ev<< "In MatrixApplication::handleMessage" << endl;
    if (msg == delayTimer)
    {
        if (active) {
            int i = 5;
            if (myNodeId==initiatorAddr) i=120;
            //diceEvent();
            sendPacket();
            debugEV << "  processing application timer." << endl;
            if (!delayTimer->isScheduled())
            {
                scheduleAt(simTime() + i + uniform(0, 0.001), delayTimer);
            }
        } else {
            cancelAndDelete(delayTimer);
            delayTimer = NULL;
        }
    }
    else if (msg->getArrivalGateId() == dataIn)
    {
        ApplPkt* applPkt = static_cast<ApplPkt*>(msg);

//        try {
//            ApplPkt* applPkt = static_cast<ApplPkt*>(msg);
//            //WiseRoutePkt* pkt = check_and_cast<WiseRoutePkt*>(msg);
//            if (applPkt->getDestAddr() == LAddress::L2BROADCAST.getInt() || applPkt->getDestAddr() == LAddress::L3BROADCAST) {
//                int messageId = applPkt->getId();
//                if (messageId > lastBroadcastId) {
//                    //message to be forwared
//                    lastBroadcastId = messageId;
//                    send(applPkt, dataOut);
//                } else {
//                    //message the node send it self and which came back (because of broadcast)
//                    delete applPkt;
//                }
//
//                // handle broadcast
//            }
//
//        } catch (int e) {
//
//        }
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

void MyTestApplication::handleHostState(const HostState& state) {
    if(notAffectedByHostState)
        return;

    if(state.get() != HostState::ACTIVE) {
        active = false;
    } else {
        active = true;
    }
}
