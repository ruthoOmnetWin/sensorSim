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
import sensortechnology.src.SensorNode.Sensor.SensingUnit.SensingUnitInterface;
import sensortechnology.src.SensorNode.Sensor.SensingUnit.AbstractSensingUnit;
import sensortechnology.src.SensorNode.Sensor.SignalConditioner.SignalConditionerInterface;
import sensortechnology.src.SensorNode.Sensor.SignalConditioner.AbstractSignalConditioner;
import sensortechnology.src.SensorNode.Sensor.SignalConverter.SignalConverterInterface;
import sensortechnology.src.SensorNode.Sensor.SignalConverter.AbstractSignalConverter;
import sensortechnology.src.SensorNode.Sensor.Transducer.TransducerInterface;
import sensortechnology.src.SensorNode.Sensor.Transducer.AbstractTransducer;
//
// TODO auto-generated module
//
module AbstractSensor like SensorInterface
{
    parameters:
        string type;

        @display("i=block/join");
    gates:
        //both gates get connected dynamically inside AbstractSensorNode, but after the 
        //check for unconnected gates, so it is declared loose but never will be unconnected
        output fromTransducerToNodeProcessor @loose;
        input toSensingUnitFromNodeProcessor @loose;

    submodules:
        SensingUnit: <"SensingUnit"+type> like SensingUnitInterface {
            @display("p=100,50");
        }
        SignalConditioner: <"SignalConditioner"+type> like SignalConditionerInterface {

            @display("p=100,120");
        }
        SignalConverter: <"SignalConverter"+type> like SignalConverterInterface {

            @display("p=100,190");
        }
        Transducer: <"Transducer"+type> like TransducerInterface {
            @display("p=100,260");
        }

    connections:
        SensingUnit.toSignalConditioner --> ned.DelayChannel --> SignalConditioner.fromSensingUnit;
        SignalConditioner.toSignalConverter --> ned.DelayChannel --> SignalConverter.fromSignalConditioner;
        SignalConverter.toTransducer --> ned.DelayChannel --> Transducer.fromSignalConverter;
        Transducer.toNodeProcessor --> ned.DelayChannel --> fromTransducerToNodeProcessor;
        toSensingUnitFromNodeProcessor --> ned.DelayChannel --> SensingUnit.fromNodeProcessor;

}
