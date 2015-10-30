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

import org.mixim.modules.node.WirelessNode;

import org.mixim.base.modules.BaseNetwork;

network ApplicationClusteringImplementations extends BaseNetwork
{
    parameters:
        int numNodes; // total number of hosts in the network

        @display("bgi=background/floorplan;bgb=856,323");
    submodules:
        testPos: WirelessNode {
            @display("p=59,50");
        }
        testPos1: WirelessNode {
            @display("p=232,50");
        }
        testPos2: WirelessNode {
            @display("p=59,98");
        }
        testPos3: WirelessNode {
            @display("p=59,146");
        }
        testPos4: WirelessNode {
            @display("p=59,260");
        }
        testPos5: WirelessNode {
            @display("p=165,45");
        }
        testPos6: WirelessNode {
            @display("p=165,100");
        }
        testPos7: WirelessNode {
            @display("p=165,175");
        }
        testPos8: WirelessNode {
            @display("p=122,257");
        }
        testPos9: WirelessNode {
            @display("p=169,257");
        }
        testPos10: WirelessNode {
            @display("p=219,257");
        }
        testPos11: WirelessNode {
            @display("p=267,257");
        }
        testPos12: WirelessNode {
            @display("p=300,117");
        }
        testPos13: WirelessNode {
            @display("p=280,50");
        }
        testPos14: WirelessNode {
            @display("p=319,50");
        }
        testPos15: WirelessNode {
            @display("p=280,50");
        }
        testPos16: WirelessNode {
            @display("p=300,199");
        }
        testPos17: WirelessNode {
            @display("p=358,199");
        }
        testPos18: WirelessNode {
            @display("p=385,45");
        }
        testPos19: WirelessNode {
            @display("p=472,78");
        }
        testPos20: WirelessNode {
            @display("p=472,125");
        }
        testPos21: WirelessNode {
            @display("p=537,50");
        }
        testPos22: WirelessNode {
            @display("p=585,59");
        }
        testPos23: WirelessNode {
            @display("p=635,59");
        }
        testPos24: WirelessNode {
            @display("p=683,59");
        }
        testPos25: WirelessNode {
            @display("p=546,125");
        }
        testPos26: WirelessNode {
            @display("p=563,199");
        }
        testPos27: WirelessNode {
            @display("p=635,156");
        }
        testPos28: WirelessNode {
            @display("p=701,139");
        }
        testPos29: WirelessNode {
            @display("p=612,251");
        }
        testPos30: WirelessNode {
            @display("p=651,251");
        }
        testPos31: WirelessNode {
            @display("p=701,238");
        }
        testPos32: WirelessNode {
            @display("p=754,238");
        }
        testPos33: WirelessNode {
            @display("p=768,136");
        }
        testPos34: WirelessNode {
            @display("p=768,185");
        }
        testPos35: WirelessNode {
            @display("p=729,59");
        }
        testPos36: WirelessNode {
            @display("p=793,45");
        }
        testPos37: WirelessNode {
            @display("p=807,98");
        }
    connections allowunconnected:
    // all connections and gates are to be generated dynamically
}
