#include "MyTestApplication.h"
#include "BaseMacLayer.h"
#include "NetwControlInfo.h"
#include <omnetpp.h>
#include "GenericPacket_m.h"
#include "FindModule.h"


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



        //myApp->myBaseHost = findHost();

        myNodeId = LAddress::L3Type(par("nodeAddr").longValue());

        mySimpleBattery = new SimpleBattery();
        mySimpleBattery = FindModule<SimpleBattery*>::findSubModule(findHost());

        myPhyLayerBattery = new PhyLayerBattery();
        myPhyLayerBattery = FindModule<PhyLayerBattery*>::findSubModule(findHost());
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
    char bubblestr[32];
    if (myNodeId == 1)
    {
        GenericPacket* gPacketP = new GenericPacket();
        gPacketP->setDstId(LAddress::L2BROADCAST.getInt());
        NetwControlInfo::setControlInfo(gPacketP, LAddress::L2BROADCAST.getInt());
        send(gPacketP, dataOut);
        //findHost()->sendDelayed(gPacketP, delay, myOutGate);
        return;
    }
    else
    {
#if 1
        if (sleepState == 0)
        {
            sleepState=1;
            ev<< "Node: " << myNodeId << ": " <<  "Enter SleepMode" << endl;
            myPhyLayerBattery->setRadioState(MiximRadio::SLEEP);
            findHost()->getDisplayString().setTagArg("i2", 0, "status/red");
        }
        else
        {
            sleepState=0;
            ev<< "Node: " << myNodeId << ": " << "Leave SleepMode" << endl;
            myPhyLayerBattery->setRadioState(MiximRadio::RX);
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
        int i = 5;
        if (myNodeId==1) i=1;
        //diceEvent();
        sendPacket();
        debugEV << "  processing application timer." << endl;
        if (!delayTimer->isScheduled())
        {
            scheduleAt(simTime() + i + uniform(0, 0.001), delayTimer);
        }
    }
    else if (msg->getArrivalGateId() == dataIn)
    {
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
