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

#include "WakeupPhyLayerBattery.h"

#include "Decider80211MultiChannel.h"
#include "MacToPhyControlInfo.h"
#include "MiXiMMacPkt.h"
#include "WakeupPhyUtils.h"
#include "WakeupBaseDecider.h"
#include "SNRThresholdDecider.h"

Define_Module(WakeupPhyLayerBattery);

void WakeupPhyLayerBattery::initialize(int stage) {
    PhyLayer::initialize(stage);
    if (stage == 0) {
        cModule * const pNic = getNic();

        numActivities =
                hasPar("numActivities") ? par("numActivities").longValue() : 5;

        /* parameters belong to the NIC, not just phy layer
         *
         * if/when variable transmit power is supported, txCurrent
         * should be specified as an xml table of available transmit
         * power levels and corresponding txCurrent */
        wakeupCurrent = pNic->par("wakeupCurrent");
        setupWakeupCurrent = pNic->par("setupWakeupCurrent");
        sleepCurrent = rxCurrent = decodingCurrentDelta = txCurrent = 0;
        setupRxCurrent = setupTxCurrent = rxTxCurrent = txRxCurrent = 0;
        sleepCurrent = pNic->par("sleepCurrent");
        rxCurrent = pNic->par("rxCurrent");
        if (pNic->hasPar("decodingCurrentDelta"))
            decodingCurrentDelta = pNic->par("decodingCurrentDelta");
        txCurrent = pNic->par("txCurrent");
        setupRxCurrent = pNic->par("setupRxCurrent");
        setupTxCurrent = pNic->par("setupTxCurrent");
        rxTxCurrent = pNic->par("rxTxCurrent");
        txRxCurrent = pNic->par("txRxCurrent");
    } else {

        //radio = initializeRadio();

        registerWithBattery("physical layer", numActivities);
        setRadioCurrent(radio->getCurrentState());
    }
}

Decider* WakeupPhyLayerBattery::getDeciderFromName(const std::string& name,
        ParameterMap& params) {

    params["recordStats"] = cMsgPar("recordStats").setBoolValue(recordStats);

    if(name == "Decider80211") {
        protocolId = IEEE_80211;
        return createDecider<Decider80211>(params);
    }
    if(name == "SNRThresholdDecider"){
        protocolId = GENERIC;
        return createDecider<SNRThresholdDecider>(params);
    }
    if(name == "Decider802154Narrow") {
        protocolId = IEEE_802154_NARROW;
        return createDecider<Decider802154Narrow>(params);
    }
    if (name == "WakeupBaseDecider") {
        protocolId = IEEE_802154_NARROW;
        WakeupBaseDecider *const pDecider = new WakeupBaseDecider(this, sensitivity, findHost()->getIndex(), coreDebug);

        if (pDecider != NULL && !pDecider->initFromMap(params)) {
            opp_warning("Decider from config.xml could not be initialized correctly!");
        }

        return pDecider;
    }

    return BasePhyLayer::getDeciderFromName(name, params);
}

void WakeupPhyLayerBattery::drawCurrent(double amount, int activity) {
    if (radio->getCurrentState() == WakeupMiximRadio::RX) {
        if (amount != 0.0) {
            MiximBatteryAccess::drawCurrent(rxCurrent + amount,
                    DECIDER_ACCT + activity);
        } else {
            MiximBatteryAccess::drawCurrent(rxCurrent, RX_ACCT);
        }
    } else {
        opp_warning(
                "Decider wanted to change power consumption while radio not in state RX.");
    }
}

void WakeupPhyLayerBattery::handleUpperMessage(cMessage* msg) {
    if (battery && battery->getState() != HostState::ACTIVE) {
        coreEV << "host has FAILED, dropping msg " << msg->getName() << endl;
        delete msg;
        return;
    }

    macpkt_ptr_t pkt = static_cast<macpkt_ptr_t>(msg);
    MacToPhyControlInfo* cInfo =
            static_cast<MacToPhyControlInfo*>(pkt->getControlInfo());

    double current = calcTXCurrentForPacket(pkt, cInfo);

    if (current > 0) {
        MiximBatteryAccess::drawCurrent(current, TX_ACCT);
    }

    PhyLayer::handleUpperMessage(msg);
}

void WakeupPhyLayerBattery::handleAirFrame(airframe_ptr_t frame) {
    if (battery && battery->getState() != HostState::ACTIVE) {
        coreEV << "host has FAILED, dropping air frame msg " << frame->getName()
                      << endl;
        delete frame;
        return;
    }
    EV << "---------- AIRFRAME " << frame->getName() << endl;
    PhyLayer::handleAirFrame(frame);
}

void WakeupPhyLayerBattery::handleHostState(const HostState& state) {
    if (state.get() != HostState::ACTIVE
            && radio->getCurrentState() != WakeupMiximRadio::SLEEP) {
        coreEV
                      << "host is no longer in active state (maybe FAILED, SLEEP, OFF or BROKEN), force into sleep state!"
                      << endl;
        setRadioState(WakeupMiximRadio::SLEEP);
        // it would be good to create a radioState OFF, as well
    }
}

void WakeupPhyLayerBattery::finishRadioSwitching(bool bSendCtrlMsg /*= true */) {
    PhyLayer::finishRadioSwitching(bSendCtrlMsg);

    setRadioCurrent(radio->getCurrentState());
}

void WakeupPhyLayerBattery::setSwitchingCurrent(int from, int to) {
    double current = 0;

    if (from == to)
        return;

    switch (from) {
    case WakeupMiximRadio::RX:
        switch (to) {
        case WakeupMiximRadio::SLEEP:
            current = rxCurrent;
            break;
        case WakeupMiximRadio::TX:
            current = rxTxCurrent;
            break;
        case WakeupMiximRadio::POWERDOWN:
            current = 0;
            break;
        default:
            opp_error("Unknown radio switch! From RX to %d", to);
            break;
        }
        break;

    case WakeupMiximRadio::TX:
        switch (to) {
        case WakeupMiximRadio::POWERDOWN:
            current = 0;
            break;
        case WakeupMiximRadio::SLEEP:
            current = txCurrent;
            break;
        case WakeupMiximRadio::RX:
            current = txRxCurrent;
            break;
        default:
            opp_error("Unknown radio switch! From TX to %d", to);
            break;
        }
        break;

    case WakeupMiximRadio::SLEEP:
        switch (to) {
        case WakeupMiximRadio::TX:
            current = setupTxCurrent;
            break;
        case WakeupMiximRadio::RX:
            current = setupRxCurrent;
            break;
        case WakeupMiximRadio::POWERDOWN:
            current = 0;
            break;
        default:
            opp_error("Unknown radio switch! From SLEEP to %d", to);
            break;
        }
        break;

    default:
        opp_error("Unknown radio state: %d", from);
        break;
    }

    MiximBatteryAccess::drawCurrent(current, SWITCHING_ACCT);
}

void WakeupPhyLayerBattery::setRadioCurrent(int rs) {
    switch (rs) {
    case WakeupMiximRadio::POWERDOWN:
        MiximBatteryAccess::drawCurrent(0, POWERDOWN_ACCT);
        break;
    case WakeupMiximRadio::RX:
        MiximBatteryAccess::drawCurrent(rxCurrent, RX_ACCT);
        break;
    case WakeupMiximRadio::TX:
        MiximBatteryAccess::drawCurrent(txCurrent, TX_ACCT);
        break;
    case WakeupMiximRadio::SLEEP:
        MiximBatteryAccess::drawCurrent(sleepCurrent, SLEEP_ACCT);
        break;
    default:
        opp_error("Unknown radio state: %d", rs);
        break;
    }
}

simtime_t WakeupPhyLayerBattery::setRadioState(int rs) {
    Enter_Method_Silent
    ();
    int prevState = radio->getCurrentState();

    if (battery) {
        if (battery && battery->getState() != HostState::ACTIVE
                && rs != WakeupMiximRadio::SLEEP && prevState != rs) {
            coreEV << "can not switch radio state, host is not in active state!"
                          << endl;
            return Decider::notAgain;
        }
    }

    simtime_t endSwitch = PhyLayer::setRadioState(rs);

    if (endSwitch >= SIMTIME_ZERO) {
        if (radio->getCurrentState() == WakeupMiximRadio::SWITCHING) {
            setSwitchingCurrent(prevState, rs);
        } else {
            setRadioCurrent(radio->getCurrentState());
        }
    }

    return endSwitch;
}

void WakeupPhyLayerBattery::handleMessage(cMessage* msg) {

    //self messages
    if(msg->isSelfMessage()) {
        handleSelfMessage(msg);

    //MacPkts <- MacToPhyControlInfo
    } else if(msg->getArrivalGateId() == upperLayerIn) {
        handleUpperMessage(msg);

    //controlmessages
    } else if(msg->getArrivalGateId() == upperControlIn) {
        handleUpperControlMessage(msg);

    //AirFrames
    } else if(msg->getKind() == AIR_FRAME){
//        if (strcmp(msg->getName(), "wakeup") == 0) {
//
//            cMessage* msgDup = msg->dup();
//
//            MiximAirFrame* maf = static_cast<airframe_ptr_t>(msgDup);
//
//            cMessage* packet = maf->decapsulate();
//            assert(packet);
//    //        setUpControlInfo(packet, result);
//            sendMacPktUp(packet);
//        }
        handleAirFrame(static_cast<airframe_ptr_t>(msg));

    //unknown message
    } else {
        ev << "Unknown message received." << endl;
        delete msg;
    }
}

double WakeupPhyLayerBattery::calcTXCurrentForPacket(macpkt_ptr_t pkt, MacToPhyControlInfo* cInfo) const {
    return -1.0;
}

int WakeupPhyLayerBattery::myProtocolId() const {
    return protocolId;
}

//WakeupPhyLayerBattery::WakeupPhyLayerBattery()
//{
//    numActivities = 0;
//    sleepCurrent = 0;
//    rxCurrent = 0;
//    decodingCurrentDelta = 0;
//    txCurrent = 0;
//    setupRxCurrent = 0;
//    setupTxCurrent = 0;
//    rxTxCurrent = 0;
//    txRxCurrent = 0;
//    wakeupCurrent = 0;
//    setupWakeupCurrent = 0;
//}
