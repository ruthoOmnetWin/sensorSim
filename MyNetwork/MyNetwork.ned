package mynetwork;

import org.mixim.base.connectionManager.ConnectionManager;
import org.mixim.base.modules.BaseNetwork;
import org.mixim.base.modules.IBaseNetwLayer;
import org.mixim.modules.node.Host802154_2400MHz;
import org.mixim.base.connectionManager.IConnectionManager;

import mynetwork.WorldModel.CustomWorldUtility;
import mynetwork.Node.TNode;
import mynetwork.Node.PNode;
import mynetwork.Node.HNode;
import mynetwork.Node.THNode;

network MyNetwork //extends BaseNetwork 
{
    parameters:
        bool createNewEnvironmentData;

        int numTNodes = default(1);
        int numPNodes = default(1);
        int numHNodes = default(1);
        int numTHNodes = default(1);
        int numNodes = numTNodes + numPNodes + numHNodes + numTHNodes; // total number of hosts in the network
        string wuType = default("CustomWorldUtility");

        //BaseNetwork
        double playgroundSizeX @unit(m); // x size of the area the nodes are in (in meters)
        double playgroundSizeY @unit(m); // y size of the area the nodes are in (in meters)
        double playgroundSizeZ @unit(m); // z size of the area the nodes are in (in meters)
        **.mobility.constraintAreaMinX = default(0m);
        **.mobility.constraintAreaMinY = default(0m);
        **.mobility.constraintAreaMinZ = default(0m);
        **.mobility.constraintAreaMaxX = default(playgroundSizeX);
        **.mobility.constraintAreaMaxY = default(playgroundSizeY);
        **.mobility.constraintAreaMaxZ = default(playgroundSizeZ);
        string cmType = default("org.mixim.base.connectionManager.ConnectionManager"); // connection manager to use

        @display("bgb=475,297,white;bgp=0,0");

    submodules:
        tnode[numTNodes]: TNode {
            parameters:
                @display("i=device/card");
                numHosts = numNodes;
        }
        hnode[numHNodes]: HNode {
            parameters:
                @display("i=device/card");
                numHosts = numNodes;
        }
        pnode[numPNodes]: PNode {
            parameters:
                @display("i=device/card");
                numHosts = numNodes;
        }
        thnode[numTHNodes]: THNode {
            parameters:
                @display("i=device/card");
                numHosts = numNodes;
        }
        connectionManager: <cmType> like IConnectionManager {
            parameters:
                @display("i=abstract/multicast;is=s");
        }
        world: CustomWorldUtility {
            numGates = numNodes + numTHNodes;
            createData = createNewEnvironmentData;
        }

    connections allowunconnected: // some connections and gates are to be generated dynamically

        world.worldDataGate[i] <--> {  delay = 100ms; } <--> tnode[i].worldGate[0] for i=0..(numTNodes-1);
        world.worldDataGate[numTNodes+i] <--> {  delay = 100ms; } <--> hnode[i].worldGate[0] for i=0..(numHNodes-1);
        world.worldDataGate[numTNodes+numHNodes+i] <--> {  delay = 100ms; } <--> pnode[i].worldGate[0] for i=0..(numPNodes-1);
        //for the THNode 2 connections must exist
        world.worldDataGate[numTNodes+numHNodes+numPNodes+i] <--> {  delay = 100ms; } <--> thnode[i].worldGate[0] for i=0..((numTHNodes-1));
        world.worldDataGate[numTNodes+numHNodes+numPNodes+numTHNodes+i] <--> {  delay = 100ms; } <--> thnode[i].worldGate[1] for i=0..(numTHNodes-1);
}
