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
        numHosts = max;

        routeTree = new int[max];
        routeTreeAdjList = new AdjListElement[max];

        for (int i = 0; i < max; i++) {
            //routeTree[i] = std::stoi(v.at(i));
            routeTree[i] = atoi( v[i].c_str() );
            EV << routeTree[i] << endl;
        }

        for (int child = 0; child < max; child++) {
            int father = routeTree[child];
            if (child != father) {
                insertList(father, child);
            }

        }

        convertTreeToRouteTable();

        //output routing tables
        EV << "Routing table for " << myNetwAddr << endl;
        for (int i = 0; i < numHosts; i++) {
            EV << "target: " << i << ", next: " << getRoute(i) << endl;
        }

    }
}

/**
 * check if a given value (node id) is element of the given list
 * => check if the given node id is a child of the node's list
 */
bool CustomWiseRoute::containsElement(AdjListElement* elem, int value) {
    if (value == elem->value) {
        return true;
    }
    if (elem->next == NULL) {
        return false;
    }
    return containsElement(elem->next, value);
}

/**
 * when creating or updating the adjazenz list use this function to insert new elements
 *
 * @var int index is the position in the array routeTreeAdjList to insert
 * @var int value is the the id of the child node (of the father with id index) to be inserted
 */
void CustomWiseRoute::insertList(int index, int value) {
    AdjListElement* last = findListEnd(&routeTreeAdjList[index]);
    if (last->value != -1) {
        AdjListElement* newLast = new AdjListElement;
        last->next = newLast;
        last = newLast;
    }
    last->value = value;
}

/**
 * find the last element of a given list (AdjListElement)
 */
CustomWiseRoute::AdjListElement* CustomWiseRoute::findListEnd(AdjListElement* elem) {
    if (elem->next == NULL) {
        return elem;
    }
    return findListEnd(elem->next);
}

/**
 * add entry to the routeTable
 *
 * @var int targetAddr is the target node to be routed
 * @var int nextAddr is the next hop to be done to reach the target
 */
void CustomWiseRoute::makeEntry(int targetAddr, int nextAddr) {
    WiseRoute::tRouteTableEntry newEntry;
    newEntry.nextHop = nextAddr;
    routeTable.insert(make_pair(targetAddr, newEntry));
}

/**
 * convert the general routing tree into the node specific routing table
 */
void CustomWiseRoute::convertTreeToRouteTable() {
    //routeTree;
    //routeTable;
    //myNetwAddr;

    //list of childs of the node i are inside routeTreeAdjList[i]
    int fatherAddr = routeTree[myNetwAddr];
    if (myNetwAddr == 6) {
        EV << "father" << endl;
    }

    if (routeTreeAdjList[myNetwAddr].value == -1) {
        //no children
        //this means all other nodes can be accessed through the father
        isLeaf = true;
    } else {
        //proccess the children
        AdjListElement* currentElement = &routeTreeAdjList[myNetwAddr];

        do {
            int child = currentElement->value;
            makeEntry(child, child);

            proccessChildNodes(child);
            currentElement = currentElement->next;
        } while (currentElement != NULL);
    }

    if (myNetwAddr == fatherAddr) {
        //no father -> root
        isRoot = true;
    } else {
        //process all nodes that aren't children
        for (int i = 0; i < numHosts; i++) {
            if (!containsElement(&routeTreeAdjList[myNetwAddr], i)) {
                makeEntry(i, routeTree[myNetwAddr]);
            }
        }
    }

}

void CustomWiseRoute::proccessChildNodes(int routeAddr) {
    AdjListElement* currentElement = &routeTreeAdjList[routeAddr];
    AdjListElement* lastElement = findListEnd(currentElement);

    do {
        int child = currentElement->value;

        if (child == -1) {
            break;
        }

        makeEntry(child, routeAddr);

        //recursive
        proccessChildNodes(child);

        currentElement = currentElement->next;
    } while (currentElement != NULL);
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

