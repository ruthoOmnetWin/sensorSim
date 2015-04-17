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

package sensortechnology.src.SensorNode;
import sensortechnology.src.SensorNode.Sensor.*;
import sensortechnology.src.SensorNode.Processor.*;
import sensortechnology.src.SensorNode.Memory.*;
import org.mixim.modules.node.Host802154_2400MHz;

//
// TODO auto-generated type
//
module Host802154_2400MHzSensorNode extends Host802154_2400MHz
{
    parameters:
        bool hasTemperatureSensor;
        bool hasHumiditySensor;
        bool hasPressureSensor;
        bool hasLightSensor;
        int numSensors = default(0);
        int numSensorModules = 4;
        int numDevices = 
        	(
        		 (hasTemperatureSensor ? 1 : 0) 
            	+(hasHumiditySensor ? 1 : 0)
            	+(hasPressureSensor ? 1 : 0)
            	+(hasLightSensor ? 1 : 0)
        	) * numSensorModules //calculate number of energie accounts from sensor 
        	+ 2; //memory, processor
        @class("AbstractSensorNode");

        @display("bgb=445,450");
    submodules:
        TemperatureSensor: TemperatureSensor if hasTemperatureSensor {
            @display("p=275,51");
        }
        HumiditySensor: HumiditySensor if hasHumiditySensor {
            @display("p=275,120");
        }
        PressureSensor: PressureSensor if hasPressureSensor {
            @display("p=275,190");
        }
        LightSensor: LightSensor if hasLightSensor {
            @display("p=275,260");
        }
        Memory: AbstractMemory {
            @display("p=400,51");
        }
        //Processor is created inside the C++-Class in order to create the gates to the
        //different sensors dynamically by the input
        Processor: ExampleProcessor if false {
            @display("p=400,159");
        }
    connections:
        //these connections will never be created, they only exist to draw the model
        if false {
            HumiditySensor.fromTransducerToNodeProcessor --> Processor.fromHumiditySensor;
            TemperatureSensor.fromTransducerToNodeProcessor --> Processor.fromTemperatureSensor;
            PressureSensor.fromTransducerToNodeProcessor --> Processor.fromPressureSensor;
            LightSensor.fromTransducerToNodeProcessor --> Processor.fromLightSensor;

            HumiditySensor.toSensingUnitFromNodeProcessor <-- Processor.toHumiditySensor;
            TemperatureSensor.toSensingUnitFromNodeProcessor <-- Processor.toTemperatureSensor;
            PressureSensor.toSensingUnitFromNodeProcessor <-- Processor.toPressureSensor;
            LightSensor.toSensingUnitFromNodeProcessor <-- Processor.toLightSensor;
        }

}
