package mynetwork;

import org.mixim.base.connectionManager.ConnectionManager;
//import org.mixim.modules.node.WirelessNode;
import org.mixim.base.modules.BaseNetwork;
import org.mixim.base.modules.IBaseNetwLayer;
import org.mixim.modules.node.Host802154_2400MHz;
import mynetwork.Node.MyWirelessNode;
import mynetwork.WorldModel.CustomWorldUtility;

import org.mixim.base.connectionManager.IConnectionManager;


network MyNetwork //extends BaseNetwork 
{
    parameters:
        bool createNewEnvironmentData;
        int numNodes; // total number of hosts in the network
        int networkSensorAlgorithm;
        //postion of the data
        int networkPosX;
        int networkPosY;
        //value of the data
        int networkValue;
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
        //string wuType = default("org.mixim.base.modules.BaseWorldUtility");            // world utility to use

        @display("bgb=475,297,white;bgp=0,0");

    submodules:
        node[numNodes]: MyWirelessNode {
            parameters:
                numHosts = numNodes;
                nodePosX = networkPosX;
                nodePosY = networkPosY;
                nodeValue = networkValue;
                nodeType = networkSensorAlgorithm;
                @display("i=device/card");
        }
        connectionManager: <cmType> like IConnectionManager {
            parameters:
                @display("p=201,0;i=abstract/multicast;is=s");
        }
        world: CustomWorldUtility {
        	numGates = numNodes;    
        	createData = createNewEnvironmentData;
        };
    connections allowunconnected:
        world.worldDataGate[i] <--> {  delay = 100ms; } <--> node[i].worldGate for i=0..(numNodes-1);
    // all connections and gates are to be generated dynamically

}
