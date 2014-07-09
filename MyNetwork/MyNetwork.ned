package mynetwork;

import org.mixim.base.connectionManager.ConnectionManager;
//import org.mixim.modules.node.WirelessNode;
import org.mixim.base.modules.BaseNetwork;
import org.mixim.base.modules.IBaseNetwLayer;
import org.mixim.modules.node.Host802154_2400MHz;


network MyNetwork extends BaseNetwork 
{
    parameters:
        int numNodes; // total number of hosts in the network
        int networkSensorAlgorithm;
        //postion of the data
        int networkPosX;
        int networkPosY;
        //value of the data
        int networkValue;

    submodules:
        node[numNodes]: MyWirelessNode {
            parameters:
                numHosts = numNodes;
                nodePosX = networkPosX;
        		nodePosY = networkPosY;
        		nodeValue = networkValue;
        		nodeType = networkSensorAlgorithm;
                @display("i=device/card_l");
        }
    connections allowunconnected:
    // all connections and gates are to be generated dynamically
}
