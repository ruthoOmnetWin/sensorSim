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

//
// Sensor for Humidity that combines the simple modules SensingUnit, 
// SignalConverter, SignalConditioner and Transducer that belong to it
//
module HumiditySensor extends AbstractSensor
{
    parameters:
        type = "Humidity";
}
