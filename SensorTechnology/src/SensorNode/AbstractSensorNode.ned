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

//
// TODO auto-generated type
//
module AbstractSensorNode like SensorNodeInterface
{
    parameters:
        bool hasTemperatureSensor;
        bool hasHumiditySensor;
        bool hasPressureSensor;
        bool hasLightSensor;
        int numSensors = default(0);
        @class("AbstractSensorNode");

        //these are used to draw the overview of the model
        bool fakeProcessor = false;

        @display("bgb=245,450;i=block/ifcard");
    submodules:
        TemperatureSensor: TemperatureSensor if hasTemperatureSensor {
            @display("p=75,51");
        }
        HumiditySensor: HumiditySensor if hasHumiditySensor {
            @display("p=75,120");
        }
        PressureSensor: PressureSensor if hasPressureSensor {
            @display("p=75,190");
        }
        LightSensor: LightSensor if hasLightSensor {
            @display("p=75,260");
        }
        Memory: AbstractMemory {
            @display("p=200,51");
        }
        //Processor is created inside the C++-Class in order to create the gates to the
        //different sensors dynamically by the input
        Processor: ExampleProcessor if fakeProcessor {
            @display("p=200,159");
        }
    connections:
        //these connections will never be created, they only exist to draw the model
        //
        //the real connections between processor and sensor are created dynamically because 
        //only the gates needed are created in order to avoid unused (not connected) gates
        if fakeProcessor {
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
