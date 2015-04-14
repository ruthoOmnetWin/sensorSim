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

package mynetwork.Node;
import mynetwork.Node.Sensor.PressureSensor;

module PNode extends MyWirelessNode
{
    gates:
	    inout toSensor[1];
	    inout worldGate[1];
	    
    submodules:
        PressureSensor: PressureSensor {
            @display("p=140,310");
        }
        
    connections:
        toSensor[0] <--> {  delay = 0ms; } <--> PressureSensor.toNode;
        worldGate[0] <--> {  delay = measureTime; } <--> PressureSensor.worldDataGate;
}
