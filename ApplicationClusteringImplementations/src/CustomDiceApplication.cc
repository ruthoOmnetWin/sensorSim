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


            //setPositions();
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
//            WakeUpPacket* wuPacketP = new WakeUpPacket();
//            wuPacketP->setDestAddr(LAddress::L3BROADCAST);
//            NetwControlInfo::setControlInfo(wuPacketP, LAddress::L3BROADCAST);
//            send(wuPacketP, dataOut);
            ApplPkt* gPacketP = new ApplPkt();
            gPacketP->setName("wakeup");
            gPacketP->setDestAddr(LAddress::L3BROADCAST);
            NetwControlInfo::setControlInfo(gPacketP, LAddress::L3BROADCAST);
            send(gPacketP, dataOut);
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
