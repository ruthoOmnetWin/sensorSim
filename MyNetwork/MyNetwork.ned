package mynetwork;

//import org.mixim.modules.node.WirelessNode;
import org.mixim.base.modules.BaseNetwork;
import org.mixim.base.modules.IBaseNetwLayer;
import org.mixim.modules.node.Host802154_2400MHz;


network MyNetwork extends sensorDataBaseNetwork
{
    parameters:
        int numNodes; // total number of hosts in the network

    submodules:
        node[numNodes]: Host802154_2400MHz {
            parameters:
                numHosts = numNodes;
                @display("i=device/card_l");
        }
    connections allowunconnected:
    // all connections and gates are to be generated dynamically
}