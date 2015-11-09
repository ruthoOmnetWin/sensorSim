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
import sensortechnology.src.SensorNode.SensorNode;

network ApplicationClusteringImplementations extends BaseNetwork
{
    parameters:
        int numNodes; // total number of hosts in the network
        numNodes = 38;

        @display("bgi=background/floorplan;bgb=856,323");
        wuType = default("sensortechnology.src.WorldModel.CustomWorldUtility");
        
    submodules:   
        TemperatureSensorNode0: SensorNode {
            @display("p=59,50");
            hasTemperatureSensor = true;
            //@class(ApplicationClusteringImplementations);
        }
        TemperatureSensorNode1: SensorNode {
            @display("p=232,50");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode2: SensorNode {
            @display("p=59,98");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode3: SensorNode {
            @display("p=59,146");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode4: SensorNode {
            @display("p=59,260");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode5: SensorNode {
            @display("p=165,45");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode6: SensorNode {
            @display("p=165,100");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode7: SensorNode {
            @display("p=165,175");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode8: SensorNode {
            @display("p=122,257");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode9: SensorNode {
            @display("p=169,257");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode10: SensorNode {
            @display("p=219,257");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode11: SensorNode {
            @display("p=267,257");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode12: SensorNode {
            @display("p=300,117");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode13: SensorNode {
            @display("p=280,50");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode14: SensorNode {
            @display("p=319,50");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode15: SensorNode {
            @display("p=280,50");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode16: SensorNode {
            @display("p=300,199");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode17: SensorNode {
            @display("p=358,199");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode18: SensorNode {
            @display("p=385,45");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode19: SensorNode {
            @display("p=472,78");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode20: SensorNode {
            @display("p=472,125");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode21: SensorNode {
            @display("p=537,50");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode22: SensorNode {
            @display("p=585,59");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode23: SensorNode {
            @display("p=635,59");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode24: SensorNode {
            @display("p=683,59");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode25: SensorNode {
            @display("p=546,125");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode26: SensorNode {
            @display("p=563,199");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode27: SensorNode {
            @display("p=635,156");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode28: SensorNode {
            @display("p=701,139");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode29: SensorNode {
            @display("p=612,251");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode30: SensorNode {
            @display("p=651,251");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode31: SensorNode {
            @display("p=701,238");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode32: SensorNode {
            @display("p=754,238");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode33: SensorNode {
            @display("p=768,136");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode34: SensorNode {
            @display("p=768,185");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode35: SensorNode {
            @display("p=729,59");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode36: SensorNode {
            @display("p=793,45");
            hasTemperatureSensor = true;
        }
        TemperatureSensorNode37: SensorNode {
            @display("p=807,98");
            hasTemperatureSensor = true;
        }
    connections allowunconnected:
        
    // all connections and gates are to be generated dynamically
}