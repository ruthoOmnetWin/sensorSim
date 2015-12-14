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

network MyTestApplicationNetw extends BaseNetwork
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
            @display("p=558,334");
            //hasTemperatureSensor = true;
        }
        Node13: Sensor_Wakeup_DicePhyMacHost {
            @display("p=519,218");
            //hasTemperatureSensor = true;
        }
        
    connections allowunconnected:

    // all connections and gates are to be generated dynamically
}
