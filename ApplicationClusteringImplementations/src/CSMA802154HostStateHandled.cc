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

#include <CSMA802154HostStateHandled.h>
#include "MacPkt_m.h"
#include "WiseRoutePkt_m.h"

Define_Module(CSMA802154HostStateHandled);

CSMA802154HostStateHandled::~CSMA802154HostStateHandled() {

}

CSMA802154HostStateHandled::CSMA802154HostStateHandled() {
    active = true;
}

void CSMA802154HostStateHandled::handleHostState(const HostState& state) {
    if(notAffectedByHostState)
        return;

    if(state.get() != HostState::ACTIVE) {
        active = false;
    } else {
        active = true;
    }
}

void CSMA802154HostStateHandled::initialize(int stage) {
    CSMA802154::initialize(stage);
    active = true;
}

cPacket* CSMA802154HostStateHandled::decapsMsg(macpkt_ptr_t macPkt) {
    if (active) {
        return CSMA802154::decapsMsg(macPkt);
    } else {
        //delete macPkt;
        return NULL;
    }
}

void CSMA802154HostStateHandled::handleLowerControl(cMessage *msg) {
    if (active) {
        CSMA802154::handleLowerControl(msg);
    } else {
        delete msg;
    }
}
