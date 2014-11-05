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
import mynetwork.Node.LNode;

import mynetwork.Node.THNode;
import mynetwork.Node.TLNode;
import mynetwork.Node.TPNode;
import mynetwork.Node.HLNode;
import mynetwork.Node.HPNode;
import mynetwork.Node.LPNode;

import mynetwork.Node.THLNode;
import mynetwork.Node.TLPNode;
import mynetwork.Node.THPNode;
import mynetwork.Node.HLPNode;

import mynetwork.Node.THLPNode;

network MyNetwork //extends BaseNetwork 
{
    parameters:
        bool createNewEnvironmentData;

		//these parameters are only for a more clear naming in the omnet ini
        int howManyTemperatureNodes = default(1);
        int howManyPressureNodes = default(1);
        int howManyHumidityNodes = default(1);
        int howManyLightNodes = default(1);

        int howManyHumidityAndTemperatureNodes = default(0);
        int howManyTemperatureAndPressureNodes = default(0);
        int howManyHumidityAndPressureNodes = default(0);
        int howManyTemperatureAndHumidityAndPressureNodes = default(0);
        int howManyLightAndHumidityNodes = default(0);
        int howManyLightAndTemperatureNodes = default(0);
        int howManyLightAndPressureNodes = default(0);

        int howManyLightAndPressureAndHumidityNodes = default(0);
        int howManyLightAndPressureAndTemperatureNodes = default(0);
        int howManyLightAndHumidityAndTemperatureNodes = default(0);
        int howManyPressureAndHumidityAndTemperatureNodes = default(0);

        int howManyLightAndPressureAndHumidityAndTemperatureNodes = default(0);

		//these parameters are actually in use by the network
        int numTNodes = howManyTemperatureNodes;
        int numPNodes = howManyPressureNodes;
        int numHNodes = howManyHumidityNodes;
        int numLNodes = howManyLightNodes;

        int numTHNodes = howManyHumidityAndTemperatureNodes;
        int numTLNodes = howManyLightAndTemperatureNodes;
        int numTPNodes = howManyTemperatureAndPressureNodes;
        int numHLNodes = howManyLightAndHumidityNodes;
        int numHPNodes = howManyHumidityAndPressureNodes;
        int numLPNodes = howManyLightAndPressureNodes;

        int numTHLNodes = howManyLightAndHumidityAndTemperatureNodes;
        int numTLPNodes = howManyLightAndPressureAndTemperatureNodes;
        int numTHPNodes = howManyPressureAndHumidityAndTemperatureNodes;
        int numHLPNodes = howManyLightAndPressureAndHumidityNodes;

        int numTHLPNodes = howManyLightAndPressureAndHumidityAndTemperatureNodes;

        // total number of hosts in the network
        int numNodes = numTNodes + numPNodes + numHNodes + numLNodes 
        + numTHNodes + numTLNodes + numTPNodes + numHLNodes + numHPNodes + numLPNodes
        + numTHLNodes + numTLPNodes + numTHPNodes + numHLPNodes
        + numTHLPNodes;
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

        @display("bgi=maps/germany,bgb,$playgroundSizeX,$playgroundSizeY,white;bgp=0,0;bgb=$playgroundSizeX,$playgroundSizeY");

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
        //new nodes
        lnode[numLNodes]: LNode {
            parameters:
                @display("i=device/card");
                numHosts = numNodes;
        }
        tlnode[numTLNodes]: TLNode {
            parameters:
                @display("i=device/card");
                numHosts = numNodes;
        }
        tpnode[numTPNodes]: TPNode {
            parameters:
                @display("i=device/card");
                numHosts = numNodes;
        }
        hlnode[numHLNodes]: HLNode {
            parameters:
                @display("i=device/card");
                numHosts = numNodes;
        }
        hpnode[numHPNodes]: HPNode {
            parameters:
                @display("i=device/card");
                numHosts = numNodes;
        }
        lpnode[numLPNodes]: LPNode {
            parameters:
                @display("i=device/card");
                numHosts = numNodes;
        }
        thlnode[numTHLNodes]: THLNode {
            parameters:
                @display("i=device/card");
                numHosts = numNodes;
        }
        tlpnode[numTLPNodes]: TLPNode {
            parameters:
                @display("i=device/card");
                numHosts = numNodes;
        }
        thpnode[numTHPNodes]: THPNode {
            parameters:
                @display("i=device/card");
                numHosts = numNodes;
        }
        hlpnode[numHLPNodes]: HLPNode {
            parameters:
                @display("i=device/card");
                numHosts = numNodes;
        }
        thlpnode[numTHLPNodes]: THLPNode {
            parameters:
                @display("i=device/card");
                numHosts = numNodes;
        }

        connectionManager: <cmType> like IConnectionManager {
            parameters:
                @display("i=abstract/multicast;is=s");
        }
        world: CustomWorldUtility {
            //for every sensor (NOT only every node) there is one gate needed
            numGates = numNodes 
            + numTHNodes + numTLNodes + numTPNodes + numHLNodes + numHPNodes + numLPNodes 
            + 2*numTHLNodes + 2*numTLPNodes + 2*numTHPNodes + 2*numHLPNodes 
            + 3*numTHLPNodes;
            numSensorNodes = numNodes;
            createData = createNewEnvironmentData;
        }

    connections allowunconnected: // some connections and gates are to be generated dynamically

        world.worldDataGate++ <--> {  delay = 100ms; } <--> tnode[i].worldGate[0] for i=0..(numTNodes-1);
        world.worldDataGate++ <--> {  delay = 100ms; } <--> hnode[i].worldGate[0] for i=0..(numHNodes-1);
        world.worldDataGate++ <--> {  delay = 100ms; } <--> pnode[i].worldGate[0] for i=0..(numPNodes-1);
        world.worldDataGate++ <--> {  delay = 100ms; } <--> lnode[i].worldGate[0] for i=0..(numLNodes-1);

        //for the dual sensor nodes 2 connections must exist
        world.worldDataGate++ <--> {  delay = 100ms; } <--> thnode[i].worldGate[0] for i=0..((numTHNodes-1));
        world.worldDataGate++ <--> {  delay = 100ms; } <--> thnode[i].worldGate[1] for i=0..(numTHNodes-1);

        world.worldDataGate++ <--> {  delay = 100ms; } <--> tlnode[i].worldGate[0] for i=0..((numTLNodes-1));
        world.worldDataGate++ <--> {  delay = 100ms; } <--> tlnode[i].worldGate[1] for i=0..(numTLNodes-1);

        world.worldDataGate++ <--> {  delay = 100ms; } <--> tpnode[i].worldGate[0] for i=0..((numTPNodes-1));
        world.worldDataGate++ <--> {  delay = 100ms; } <--> tpnode[i].worldGate[1] for i=0..(numTPNodes-1);

        world.worldDataGate++ <--> {  delay = 100ms; } <--> hlnode[i].worldGate[0] for i=0..((numHLNodes-1));
        world.worldDataGate++ <--> {  delay = 100ms; } <--> hlnode[i].worldGate[1] for i=0..(numHLNodes-1);

        world.worldDataGate++ <--> {  delay = 100ms; } <--> hpnode[i].worldGate[0] for i=0..((numHPNodes-1));
        world.worldDataGate++ <--> {  delay = 100ms; } <--> hpnode[i].worldGate[1] for i=0..(numHPNodes-1);

        world.worldDataGate++ <--> {  delay = 100ms; } <--> lpnode[i].worldGate[0] for i=0..((numLPNodes-1));
        world.worldDataGate++ <--> {  delay = 100ms; } <--> lpnode[i].worldGate[1] for i=0..(numLPNodes-1);

        //for the triple sensor nodes 3 connections must exist
        world.worldDataGate++ <--> {  delay = 100ms; } <--> thlnode[i].worldGate[0] for i=0..((numTHLNodes-1));
        world.worldDataGate++ <--> {  delay = 100ms; } <--> thlnode[i].worldGate[1] for i=0..(numTHLNodes-1);
        world.worldDataGate++ <--> {  delay = 100ms; } <--> thlnode[i].worldGate[2] for i=0..((numTHLNodes-1));

        world.worldDataGate++ <--> {  delay = 100ms; } <--> tlpnode[i].worldGate[0] for i=0..((numTLPNodes-1));
        world.worldDataGate++ <--> {  delay = 100ms; } <--> tlpnode[i].worldGate[1] for i=0..(numTLPNodes-1);
        world.worldDataGate++ <--> {  delay = 100ms; } <--> tlpnode[i].worldGate[2] for i=0..((numTLPNodes-1));

        world.worldDataGate++ <--> {  delay = 100ms; } <--> thpnode[i].worldGate[0] for i=0..((numTHPNodes-1));
        world.worldDataGate++ <--> {  delay = 100ms; } <--> thpnode[i].worldGate[1] for i=0..(numTHPNodes-1);
        world.worldDataGate++ <--> {  delay = 100ms; } <--> thpnode[i].worldGate[2] for i=0..((numTHPNodes-1));

        world.worldDataGate++ <--> {  delay = 100ms; } <--> hlpnode[i].worldGate[0] for i=0..((numHLPNodes-1));
        world.worldDataGate++ <--> {  delay = 100ms; } <--> hlpnode[i].worldGate[1] for i=0..(numHLPNodes-1);
        world.worldDataGate++ <--> {  delay = 100ms; } <--> hlpnode[i].worldGate[2] for i=0..((numHLPNodes-1));

        //for the quad sensor node 4 connections must exist
        world.worldDataGate++ <--> {  delay = 100ms; } <--> thlpnode[i].worldGate[0] for i=0..((numTHLPNodes-1));
        world.worldDataGate++ <--> {  delay = 100ms; } <--> thlpnode[i].worldGate[1] for i=0..(numTHLPNodes-1);
        world.worldDataGate++ <--> {  delay = 100ms; } <--> thlpnode[i].worldGate[2] for i=0..((numTHLPNodes-1));
        world.worldDataGate++ <--> {  delay = 100ms; } <--> thlpnode[i].worldGate[3] for i=0..((numTHLPNodes-1));


        world.toNode++ <--> {  delay = 0ms; } <--> tnode[i].toWorld for i=0..(numTNodes-1);
        world.toNode++ <--> {  delay = 0ms; } <--> hnode[i].toWorld for i=0..(numHNodes-1);
        world.toNode++ <--> {  delay = 0ms; } <--> pnode[i].toWorld for i=0..(numPNodes-1);
        world.toNode++ <--> {  delay = 0ms; } <--> lnode[i].toWorld for i=0..(numLNodes-1);
        world.toNode++ <--> {  delay = 0ms; } <--> thnode[i].toWorld for i=0..(numTHNodes-1);
        world.toNode++ <--> {  delay = 0ms; } <--> tlnode[i].toWorld for i=0..(numTLNodes-1);
        world.toNode++ <--> {  delay = 0ms; } <--> tpnode[i].toWorld for i=0..(numTPNodes-1);
        world.toNode++ <--> {  delay = 0ms; } <--> hlnode[i].toWorld for i=0..(numHLNodes-1);
        world.toNode++ <--> {  delay = 0ms; } <--> hpnode[i].toWorld for i=0..(numHPNodes-1);
        world.toNode++ <--> {  delay = 0ms; } <--> lpnode[i].toWorld for i=0..(numLPNodes-1);
        world.toNode++ <--> {  delay = 0ms; } <--> thlnode[i].toWorld for i=0..(numTHLNodes-1);
        world.toNode++ <--> {  delay = 0ms; } <--> tlpnode[i].toWorld for i=0..(numTLPNodes-1);
        world.toNode++ <--> {  delay = 0ms; } <--> thpnode[i].toWorld for i=0..(numTHPNodes-1);
        world.toNode++ <--> {  delay = 0ms; } <--> hlpnode[i].toWorld for i=0..(numHLPNodes-1);
        world.toNode++ <--> {  delay = 0ms; } <--> thlpnode[i].toWorld for i=0..(numTHLPNodes-1);
}
