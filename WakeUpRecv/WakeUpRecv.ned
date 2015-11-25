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

package wakeuprecv;

import org.mixim.base.modules.BaseNetwork;

network WakeUpRecv extends BaseNetwork
{
    parameters:
        int numNodes; // total number of hosts in the network

        @display("bgb=364,473");
    submodules:

        node1: WakeupPhyMacHost {
            parameters:
                @display("p=94,201;b=42,42,rect,yellow;i=old/proc1,red,0;is=n;i2=status/green");
                applicationType = "MyTestApplication";

        }
        node2: WakeupPhyMacHost {
            parameters:
                @display("p=192,114;b=42,42,rect,yellow;i=old/proc1,red,0;is=n;i2=-");
                applicationType = "MyTestApplication";

        }

        node3: WakeupPhyMacHost {
            parameters:
                @display("p=192,285;b=42,42,rect,yellow;i=old/proc1,red,0;is=n;i2=status/green");
                applicationType = "MyTestApplication";
        }


    //    node0: Host802154 {
    //        @display("p=149,137");
    //    }
    //    node1: Host802154 {
    //        @display("p=372,119");
    //    }
    //    node2: Host802154 {
    //        @display("p=323,294");
    //    }
    connections allowunconnected:
    // all connections and gates are to be generated dynamically
}
