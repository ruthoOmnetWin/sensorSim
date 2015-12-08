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
            hasTemperatureSensor = true;
			applicationType = "MyTestApplication";
        }
        Node1: Sensor_Wakeup_DicePhyMacHost {
            @display("p=377,116");
            hasTemperatureSensor = true;
            applicationType = "MyTestApplication";
        }
        Node2: Sensor_Wakeup_DicePhyMacHost {
            @display("p=257,88");
            hasTemperatureSensor = true;
            applicationType = "MyTestApplication";
        }
        Node3: Sensor_Wakeup_DicePhyMacHost {
            @display("p=193,142");
            hasTemperatureSensor = true;
            applicationType = "MyTestApplication";
        }
        Node4: Sensor_Wakeup_DicePhyMacHost {
            @display("p=91,103");
            hasTemperatureSensor = true;
            applicationType = "MyTestApplication";
        }
        Node5: Sensor_Wakeup_DicePhyMacHost {
            @display("p=401,328");
            hasTemperatureSensor = true;
            applicationType = "MyTestApplication";
        }
        Node6: Sensor_Wakeup_DicePhyMacHost {
            @display("p=296,367");
            hasTemperatureSensor = true;
            applicationType = "MyTestApplication";
        }
        Node7: Sensor_Wakeup_DicePhyMacHost {
            @display("p=240,280");
            hasTemperatureSensor = true;
            applicationType = "MyTestApplication";
        }
        Node8: Sensor_Wakeup_DicePhyMacHost {
            @display("p=170,374");
            hasTemperatureSensor = true;
            applicationType = "MyTestApplication";
        }
        
    connections allowunconnected:

    // all connections and gates are to be generated dynamically
}
