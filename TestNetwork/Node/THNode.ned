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
import mynetwork.Node.Sensor.TemperatureSensor;
import mynetwork.Node.Sensor.HumiditySensor;

module THNode extends MyWirelessNode
{        
    gates:
	    inout toSensor[2];
	    inout worldGate[2];
	    
    submodules:
        TemperatureSensor: TemperatureSensor {
            @display("p=140,380");
        }
        HumiditySensor: HumiditySensor {
            @display("p=140,310");
        }
        
    connections:
        toSensor[0] <--> {  delay = 0ms; } <--> TemperatureSensor.toNode;
        worldGate[0] <--> {  delay = measureTime; } <--> TemperatureSensor.worldDataGate;
        
        toSensor[1] <--> {  delay = 0ms; } <--> HumiditySensor.toNode;
        worldGate[1] <--> {  delay = measureTime; } <--> HumiditySensor.worldDataGate;
}
