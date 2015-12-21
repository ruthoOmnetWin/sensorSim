//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <CustomDiceApplication.h>

Define_Module(CustomDiceApplication);

void CustomDiceApplication::handleMessage(cMessage * msg)
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


            //setPositions(); -> in this examples positions must be kept
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
            wuPacketP->setDestAddr(LAddress::L3BROADCAST);
            wuPacketP->setName("WakeUpReceiverPacket");
            NetwControlInfo::setControlInfo(wuPacketP, LAddress::L3BROADCAST);
            send(wuPacketP, dataOut);
            //sendDown(gPacketP);
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

void CustomDiceApplication::handleHostState(const HostState& state)
{
       if(notAffectedByHostState)
           return;

       if(state.get() != HostState::ACTIVE) {
           active = false;
       } else {
           active = true;
       }
   }
