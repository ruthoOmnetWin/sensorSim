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

package applicationclusteringimplementations;

import org.mixim.base.modules.BaseNetwork;

network ApplicationClusteringImplementations extends BaseNetwork
{
    parameters:
        int numNodes; // total number of hosts in the network
        numNodes = 38;

        //@display("bgi=floorplan;bgb=867,430");
        @display("bgi=../../sensorSim/ApplicationClusteringImplementations/src/img/rooms;bgb=801,601");
        wuType = default("sensortechnology.src.WorldModel.CustomWorldUtility");

    submodules:
        Node0: Sensor_Wakeup_DicePhyMacHost {
            @display("p=400,280");
            //hasTemperatureSensor = true;
                    //@class(ApplicationClusteringImplementations);
        }
        Node1: Sensor_Wakeup_DicePhyMacHost {
            @display("p=280,191");
            //hasTemperatureSensor = true;
        }
        Node2: Sensor_Wakeup_DicePhyMacHost {
            @display("p=249,84");
            //hasTemperatureSensor = true;
        }
        Node3: Sensor_Wakeup_DicePhyMacHost {
            @display("p=132,171");
            //hasTemperatureSensor = true;
        }
        Node4: Sensor_Wakeup_DicePhyMacHost {
            @display("p=162,84");
            //hasTemperatureSensor = true;
        }
        Node5: Sensor_Wakeup_DicePhyMacHost {
            @display("p=280,280");
            //hasTemperatureSensor = true;
        }
        Node6: Sensor_Wakeup_DicePhyMacHost {
            @display("p=218,337");
            //hasTemperatureSensor = true;
        }
        Node7: Sensor_Wakeup_DicePhyMacHost {
            @display("p=179,230");
            //hasTemperatureSensor = true;
        }
        Node8: Sensor_Wakeup_DicePhyMacHost {
            @display("p=132,298");
            //hasTemperatureSensor = true;
        }
        Node9: Sensor_Wakeup_DicePhyMacHost {
            @display("p=326,109");
            //hasTemperatureSensor = true;
        }
        Node10: Sensor_Wakeup_DicePhyMacHost {
            @display("p=361,60");
            //hasTemperatureSensor = true;
        }
        Node11: Sensor_Wakeup_DicePhyMacHost {
            @display("p=439,60");
            //hasTemperatureSensor = true;
        }
        Node12: Sensor_Wakeup_DicePhyMacHost {
            @display("p=470,123");
            //hasTemperatureSensor = true;
        }
        Node13: Sensor_Wakeup_DicePhyMacHost {
            @display("p=400,191");
            //hasTemperatureSensor = true;
        }
//        Node14: Sensor_Wakeup_DicePhyMacHost {
//            @display("p=597,555");
//            //hasTemperatureSensor = true;
//        }
//        Node15: Sensor_Wakeup_DicePhyMacHost {
//            @display("p=652,349");
//            //hasTemperatureSensor = true;
//        }
//        Node16: Sensor_Wakeup_DicePhyMacHost {
//            @display("p=746,349");
//            //hasTemperatureSensor = true;
//        }
        //        Node17: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=411,125");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node18: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=385,45");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node19: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=472,78");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node20: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=472,125");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node21: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=537,50");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node22: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=585,59");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node23: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=635,59");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node24: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=683,59");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node25: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=546,125");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node26: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=563,199");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node27: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=635,156");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node28: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=701,139");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node29: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=612,251");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node30: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=651,251");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node31: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=701,238");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node32: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=754,238");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node33: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=768,136");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node34: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=768,185");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node35: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=729,59");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node36: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=793,45");
        //            //hasTemperatureSensor = true;
        //        }
        //        Node37: Sensor_Wakeup_DicePhyMacHost {
        //            @display("p=807,98");
        //            //hasTemperatureSensor = true;
        //        }
    //        Node38: Sensor_Wakeup_DicePhyMacHost {
    //            @display("p=258,125");
    //            //hasTemperatureSensor = true;
    //        }
    connections allowunconnected:

    // all connections and gates are to be generated dynamically
}
