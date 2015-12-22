package applicationclusteringimplementations;

import org.mixim.base.modules.BaseNetwork;

//
//some information about this szenario
//
//szenario2.ini is the matching ini-file
//
//it is important to name all nodes like this: Node{myNetwAddr} where myNetwAddr == arp.offset.
////for example if arp.offset = 3 then the netwl.myNetwAddr will 3, too.
////in this case you must name the node Node3
//
////most values are similar to szenario1
//
//what happens in the szenario:
//
////leaf nodes (that measure sensor data) will never send their data on their own.
////leaf nodes will never use their sensors on their own.
////the coordinator node will ask the nodes for their data instead.
////the cluster master nodes will then search for the nodes with the highest battery power left (one for each sensor type).
////for each type the chosen node will then make one measuring and send it to the cluster master which will forward it to the global master.
//
//module types
//
////there must be one coordinator/master node (coordinatorNodeAddr), this node must use the appl layer MasterClusterAppl.
////direct childs of the master are ClusterMaster. they must use the appl layer ClusterMasterClusterAppl.
////the leaf nodes in the routing tree should connect directly to a clusterMaster. they must use the appl layer LeafClusterAppl.
//
//organize cluster
//
////use the given module types to define one Master and muliple clusters with one ClusterMaster and multiple Leafs for each
////define special cluster information inside the ClusterMaster, is will be transferred to the Leafs automatically
////these informations can be: room number
network Szenario2 extends BaseNetwork
{
    parameters:
        int numNodes; // total number of hosts in the network
        numNodes = 38;

        @display("bgi=background/roomsBigger;bgb=867,430");
        wuType = default("sensortechnology.src.WorldModel.CustomWorldUtility");
        cmType = default("org.mixim.base.connectionManager.ConnectionManager");

    submodules:
        Node0: Sensor_Wakeup_DicePhyMacHost {
            @display("p=408,218");
            //hasTemperatureSensor = true;
                    //@class(ApplicationClusteringImplementations);
        }
        Node1: Sensor_Wakeup_DicePhyMacHost {
            @display("p=311,154");
            //hasTemperatureSensor = true;
        }
        Node2: Sensor_Wakeup_DicePhyMacHost {
            @display("p=303,64");
            //hasTemperatureSensor = true;
        }
        Node3: Sensor_Wakeup_DicePhyMacHost {
            @display("p=193,142");
            //hasTemperatureSensor = true;
        }
        Node4: Sensor_Wakeup_DicePhyMacHost {
            @display("p=241,77");
            //hasTemperatureSensor = true;
        }
        Node5: Sensor_Wakeup_DicePhyMacHost {
            @display("p=342,296");
            //hasTemperatureSensor = true;
        }
        Node6: Sensor_Wakeup_DicePhyMacHost {
            @display("p=342,381");
            //hasTemperatureSensor = true;
        }
        Node7: Sensor_Wakeup_DicePhyMacHost {
            @display("p=232,277");
            //hasTemperatureSensor = true;
        }
        Node8: Sensor_Wakeup_DicePhyMacHost {
            @display("p=241,373");
            //hasTemperatureSensor = true;
        }
        Node9: Sensor_Wakeup_DicePhyMacHost {
            @display("p=558,103");
            //hasTemperatureSensor = true;
        }
        Node10: Sensor_Wakeup_DicePhyMacHost {
            @display("p=619,172");
            //hasTemperatureSensor = true;
        }
        Node11: Sensor_Wakeup_DicePhyMacHost {
            @display("p=619,257");
            //hasTemperatureSensor = true;
        }
        Node12: Sensor_Wakeup_DicePhyMacHost {
            @display("p=558,326");
            //hasTemperatureSensor = true;
        }
        Node13: Sensor_Wakeup_DicePhyMacHost {
            @display("p=519,218");
            //hasTemperatureSensor = true;
        }

    connections allowunconnected:

    // all connections and gates are to be generated dynamically
}
