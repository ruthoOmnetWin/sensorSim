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

#ifndef CUSTOMWISEROUTE_H_
#define CUSTOMWISEROUTE_H_

#include <WiseRoute.h>
#include <omnetpp.h>
#include <DummyRoutePkt_m.h>

class CustomWiseRoute : public WiseRoute
{

public:
    CustomWiseRoute();

    //special omnet methods

    void initialize(int stage);
    void finish();

    //methods for initialization of the routeTable

    void convertTreeToRouteTable();
    void makeEntry(int targetAddr, int nextAddr);
    void proccessChildNodes(int routeAddr, int father);

    struct AdjListElement {
        int value = -1;
        AdjListElement* next = NULL;
    };

    AdjListElement* getChildNodes(int nodeId);
    AdjListElement* findListEnd(AdjListElement*);
    void insertList(int index, int value);
    bool containsElement(AdjListElement* elem, int value);

    int* routeTree;
    AdjListElement* routeTreeAdjList;
    int numHosts;
    bool isRoot;
    bool isLeaf;
    bool active;

protected:

    bool stats, trace;

    int networkID;  // the network to which we belong
    int ip;  // the network to which we belong

    void handleLowerMsg(cMessage* msg);
    void handleUpperControl(cMessage *msg);
    void handleLowerControl(cMessage *msg);
    void handleUpperMsg(cMessage* msg);
    netwpkt_ptr_t encapsMsg(cPacket *appPkt);
    cPacket* decapsMsg(netwpkt_ptr_t msg);

    void handleHostState(const HostState& state);
};

#endif /* CUSTOMWISEROUTE_H_ */
