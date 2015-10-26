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

package applicationClustering;

import org.mixim.base.modules.BaseNetwork;
import org.mixim.modules.power.battery.BatteryStats;
import org.mixim.modules.power.battery.SimpleBattery;

network ApplicationClustering extends BaseNetwork
{
    parameters:
        int numNodes; // total number of hosts in the network

        @display("bgb=500,414");

    submodules:

        node1: DicePhyMacHost {
            parameters:
                @display("p=100,100;b=42,42,rect,yellow;i=led/gray30,red,0;is=n;i2=-");
                applicationType = "MatrixApplication";

        }
        node2: DicePhyMacHost {
            parameters:
                @display("p=200,100;b=42,42,rect,yellow;i=led/gray30,red,0;is=n;i2=-");
                applicationType = "MatrixApplication";

        }
        node3: DicePhyMacHost {
            parameters:
                @display("p=300,100;b=42,42,rect,yellow,blue,3;i=led/gray30,red,0;is=n;i2=-");
                applicationType = "MatrixApplication";

        }

        node4: DicePhyMacHost {
            parameters:
                @display("p=100,200;b=42,42,rect,yellow;i=led/gray30,red,0;is=n;i2=-");
                applicationType = "MatrixApplication";

        }
        node5: DicePhyMacHost {
            parameters:
                @display("p=200,200;b=42,42,rect,yellow;i=led/gray30,red,0;is=n;i2=-");
                applicationType = "MatrixApplication";

        }
        node6: DicePhyMacHost {
            parameters:
                @display("p=300,200;b=42,42,rect,yellow;i=led/gray30,red,0;is=n;i2=-");
                applicationType = "MatrixApplication";

        }

        node7: DicePhyMacHost {
            parameters:
                @display("p=100,300;b=42,42,rect,yellow;i=led/gray30,red,0;is=n;i2=-");
                applicationType = "MatrixApplication";

        }
        node8: DicePhyMacHost {
            parameters:
                @display("p=200,300;b=42,42,rect,yellow;i=led/gray30,red,0;is=n;i2=-");
                applicationType = "MatrixApplication";

        }
        node9: DicePhyMacHost {
            parameters:
                @display("p=300,300;b=42,42,rect,yellow;i=led/gray30,red,0;is=n;i2=-");
                applicationType = "MatrixApplication";

        }

        node10: DicePhyMacHost {
            parameters:
                @display("p=450,250;b=42,42,rect,yellow;i=led/gray30,red,0;is=n;i2=-");
                applicationType = "MatrixApplication";
        }
        node11: DicePhyMacHost {
            parameters:
                @display("p=431,59;b=50,50,,white;i=dice/Dice6a,white,100;is=n;i2=-");
                applicationType = "DiceApplication";
        }

    //        node11: Host802154 {
    //            @display("p=391,70");
    //        }
    connections allowunconnected:
    // all connections and gates are to be generated dynamically
}
