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

#include <CustomWiseRoute.h>

#include <limits>
#include <algorithm>
#include <cassert>

#include "NetwControlInfo.h"
#include "MacToNetwControlInfo.h"
#include "ArpInterface.h"
#include "FindModule.h"
#include "WiseRoutePkt_m.h"
#include "SimTracer.h"
#include "SensorNode.h"

using std::make_pair;

Define_Module(CustomWiseRoute);

CustomWiseRoute::CustomWiseRoute() : WiseRoute() {

}

void CustomWiseRoute::initialize(int stage) {
    WiseRoute::initialize(stage);

    if (stage == 1) {
        SensorNode* node = (SensorNode*) this->getParentModule();
        const char *vstr = node->par("routeTree").stringValue();
        std::vector<std::string> v = cStringTokenizer(vstr).asVector();
        int max = v.size();

        routeTree = new int[max];

        for (int i = 0; i < max; i++) {
            //routeTree[i] = std::stoi(v.at(i));
            routeTree[i] = atoi( v[i].c_str() );
            EV << routeTree[i] << endl;
        }

        convertTreeToRouteTable();

        numHosts = node->par("numHosts");
    }
}

WiseRoute::tRouteTableEntry CustomWiseRoute::makeEntry(int nextAddr) {
    WiseRoute::tRouteTableEntry newEntry;
    newEntry.nextHop = nextAddr;
    routeTable.insert(make_pair(nextAddr, newEntry));
}

void CustomWiseRoute::convertTreeToRouteTable() {
    //routeTree;
    //routeTable;
    //myNetwAddr;

    bool isLeaf = true;
    int childs[numHosts];
    int c = 0;
    for (int i = 0; i < numHosts; i++) {
        childs[i] = -1;
        if (routeTree[i] == myNetwAddr) {
            childs[c++] = i;
            isLeaf = false;
        }

    }

    if (myNetwAddr != routeTree[myNetwAddr]) {

        //not the root node
        proccessRemainingNodes();

    }


        //leaf node -> no children


        //middle node -> father and children
        proccessChildNodes();
        proccessRemainingNodes();

}

void CustomWiseRoute::proccessChildNodes() {

}

void CustomWiseRoute::proccessRemainingNodes() {

}

void CustomWiseRoute::finish() {
/*
    if (myNetwAddr == 1) {

        tRouteTableEntry toFive;
        toFive.nextHop = 5;
        routeTable.insert(make_pair(5, toFive));

        LAddress::L3Type next = getRoute(5, true);
        EV << "next: " << next << endl;
    }

    tFloodTable::iterator pos = floodTable.begin();
    tFloodTable::iterator posEnd = floodTable.end();

    EV << "my number is: " << this->floodSeqNumber << endl;
    EV << "my mac is: " << this->macaddress << endl;
    EV << "my sink is: " << this->sinkAddress << endl;
    EV << "my networkaddress is: " << myNetwAddr << endl;

    while (pos != posEnd) {
        EV << " " << pos->first << "," << pos->second << endl;
        ++pos;
    }

    this->routeTable[0];
*/
    WiseRoute::finish();
}

