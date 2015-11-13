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

import sensortechnology.src.SensorNode.SensorNode;

//
// compound module for a sensor node with wakeup receiver using the Nic802154_TI_CC2420A
//
module Sensor_Wakeup_Nic802154_TI_CC2420A extends SensorNode
{
    parameters:
        //route tree builds the networks routing as a tree, but stored as an array
        //the position in the array refers to the id of the node and the value at
        //this position must be the father of the node inside the routing tree
        //the root node inside the tree has it's own id as father value
        //
        //for example:
        //routeTree = 2 2 2
        //builds the following tree:
        //     2
        //   /  \
        //  0   1
        //
        //@see CustomWiseRoute::convertTreeToRouteTable() for more information about how
        //the conversion is done
        string routeTree;
}
