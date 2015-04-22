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
moduleinterface SensorNodeInterface
{
    parameters:
        //channel options
        double dataBandwidth;
        double controlBandwidth;
        //define sensors used
        bool hasTemperatureSensor;
        bool hasHumiditySensor;
        bool hasPressureSensor;
        bool hasLightSensor;
        //other
        int numSensors; //for the battery, amount of different sensor
        int numSensorModules; //for the battery, amount of elements inside one sensor
        int numDevices; //for the battery, = numSensors*numSensorModules
        int numHosts;
        @class("AbstractSensorNode");

        //these are used to draw the overview of the model
        bool fakeProcessor;

        @display("bgb=245,450;i=block/ifcard");
}
