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

#ifndef CSMA802154HOSTSTATEHANDLED_H_
#define CSMA802154HOSTSTATEHANDLED_H_

#include <CSMA802154.h>

class CSMA802154HostStateHandled : public CSMA802154
{
public:
    ~CSMA802154HostStateHandled();
    CSMA802154HostStateHandled();
    bool active;
protected:
    void initialize(int stage);
    void handleHostState(const HostState& state);

    //do not allow communication if host state not active
    cPacket *decapsMsg(macpkt_ptr_t macPkt);
    void handleLowerControl(cMessage *msg);
};

#endif /* CSMA802154HOSTSTATEHANDLED_H_ */
