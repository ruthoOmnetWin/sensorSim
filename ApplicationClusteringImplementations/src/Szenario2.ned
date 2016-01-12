package applicationclusteringimplementations;

import org.mixim.base.modules.BaseNetwork;

//
//some information about this szenario
//---------------------------------------
//
//szenario2.ini is the matching ini-file
//
//it is important to name all nodes like this: Node{myNetwAddr} where myNetwAddr == arp.offset.
////for example if arp.offset = 3 then the netwl.myNetwAddr will 3, too.
////in this case you must name the node Node3
//
////most values are similar to szenario1
//---------------------------------------
//
//what happens in the szenario:
//
////leaf nodes (that measure sensor data) will never send their data on their own.
////leaf nodes will never use their sensors on their own.
////the coordinator node will ask the nodes for their data instead.
////the cluster master nodes will then search for the nodes with the highest battery power left (one for each sensor type).
////for each type the chosen node will then make one measuring and send it to the cluster master which will forward it to the global master.
//---------------------------------------
//
//module types
//
////there must be one coordinator/master node (coordinatorNodeAddr), this node must use the appl layer MasterClusterAppl.
////direct childs of the master are ClusterMaster. they must use the appl layer ClusterMasterClusterAppl.
////the leaf nodes in the routing tree should connect directly to a clusterMaster. they must use the appl layer LeafClusterAppl.
//---------------------------------------
//
//organize cluster
//
////use the given module types to define one Master and muliple clusters with one ClusterMaster and multiple Leafs for each
////define special cluster information inside the ClusterMaster, is will be transferred to the Leafs automatically
////these informations can be: room number, room id (every leaf gets a second id that is only unique inside its room)
network Szenario2 extends BaseNetwork
{
    parameters:
        int numNodes; // total number of hosts in the network
        numNodes = 38;

        //@display("bgi=floorplan;bgb=867,430");
        @display("bgi=../../sensorSim/ApplicationClusteringImplementations/src/img/rooms3;bgb=801,601");
        wuType = default("sensortechnology.src.WorldModel.CustomWorldUtility");
        cmType = default("org.mixim.base.connectionManager.ConnectionManager");

    submodules:
        Node0: Sensor_Wakeup_DicePhyMacHost {
            @display("p=404,282");
            //hasTemperatureSensor = true;
                    //@class(ApplicationClusteringImplementations);
        }
        Node1: Sensor_Wakeup_DicePhyMacHost {
            @display("p=404,192");
            //hasTemperatureSensor = true;
            appl.roomNumber = 0;
        }
        Node2: Sensor_Wakeup_DicePhyMacHost {
            @display("p=443,123");
            //hasTemperatureSensor = true;
        }
        Node3: Sensor_Wakeup_DicePhyMacHost {
            @display("p=365,123");
            //hasTemperatureSensor = true;
        }
        Node4: Sensor_Wakeup_DicePhyMacHost {
            @display("p=404,123");
            //hasTemperatureSensor = true;
        }
        Node5: Sensor_Wakeup_DicePhyMacHost {
            @display("p=509,282");
            //hasTemperatureSensor = true;
            appl.roomNumber = 3;
        }
        Node6: Sensor_Wakeup_DicePhyMacHost {
            @display("p=580,243");
            //hasTemperatureSensor = true;
        }
        Node7: Sensor_Wakeup_DicePhyMacHost {
            @display("p=580,282");
            //hasTemperatureSensor = true;
        }
        Node8: Sensor_Wakeup_DicePhyMacHost {
            @display("p=580,321");
            //hasTemperatureSensor = true;
        }
        Node9: Sensor_Wakeup_DicePhyMacHost {
            @display("p=404,377");
            appl.roomNumber = 2;
                        //hasTemperatureSensor = true;
        }
        Node10: Sensor_Wakeup_DicePhyMacHost {
            @display("p=345,452");
            //hasTemperatureSensor = true;
        }
        Node11: Sensor_Wakeup_DicePhyMacHost {
            @display("p=384,452");
            //hasTemperatureSensor = true;
        }
        Node12: Sensor_Wakeup_DicePhyMacHost {
            @display("p=423,452");
            //hasTemperatureSensor = true;
        }
        Node13: Sensor_Wakeup_DicePhyMacHost {
            @display("p=462,452");
            //hasTemperatureSensor = true;

        }
        Node14: Sensor_Wakeup_DicePhyMacHost {
            @display("p=294,282");
            appl.roomNumber = 1;
            //hasTemperatureSensor = true;
        }
        Node15: Sensor_Wakeup_DicePhyMacHost {
            @display("p=209,204");
            //hasTemperatureSensor = true;
        }
        Node16: Sensor_Wakeup_DicePhyMacHost {
            @display("p=209,243");
            //hasTemperatureSensor = true;
        }
        Node17: Sensor_Wakeup_DicePhyMacHost {
            @display("p=209,282");
            //hasTemperatureSensor = true;
        }
        Node18: Sensor_Wakeup_DicePhyMacHost {
            @display("p=209,321");
            //hasTemperatureSensor = true;
        }
        Node19: Sensor_Wakeup_DicePhyMacHost {
            @display("p=209,360");
            //hasTemperatureSensor = true;
        }

    connections allowunconnected:

    // all connections and gates are to be generated dynamically
}
