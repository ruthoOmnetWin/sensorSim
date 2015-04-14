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

package sensortechnology.src.SensorNode.Sensor;
import sensortechnology.src.SensorNode.Sensor.SensingUnit.*;
import sensortechnology.src.SensorNode.Sensor.SignalConverter.*;
import sensortechnology.src.SensorNode.Sensor.SignalConditioner.*;
import sensortechnology.src.SensorNode.Sensor.Transducer.*;

module TemperatureSensor extends AbstractSensor
{
    parameters:
        type = "temperature";

        @display("bgb=200,300");
    submodules:
        SensingUnit: SensingUnitTemperature {
            @display("p=100,50");
        }
        SignalConditioner: SignalConditionerTemperature {

            @display("p=100,120");
        }
        SignalConverter: SignalConverterTemperature {

            @display("p=100,190");
        }
        Transducer: TransducerTemperature {
            @display("p=100,260");
        }

    connections:
        SensingUnit.toSignalConditioner --> ned.DelayChannel --> SignalConditioner.fromSensingUnit;
        SignalConditioner.toSignalConverter --> ned.DelayChannel --> SignalConverter.fromSignalConditioner;
        SignalConverter.toTransducer --> ned.DelayChannel --> Transducer.fromSignalConverter;
}
