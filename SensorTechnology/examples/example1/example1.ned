package sensortechnology.examples.example1; 
import sensortechnology.src.SensorNode.Sensor.*;
import sensortechnology.src.SensorNode.*;
import sensortechnology.src.WorldModel.*;

import org.mixim.base.modules.BaseNetwork;

network example1 extends BaseNetwork
{
    parameters:
        int numHosts = 4 * 3;
        world.createData = false;
        world.basePath = "data/";
        world.xmlTemperature = xmldoc("data/temperature.xml");
        world.xmlPressure = xmldoc("data/pressure.xml");
        world.xmlHumidity = xmldoc("data/humidity.xml");
        world.xmlLight = xmldoc("data/light.xml");
        
        cmType = default("org.mixim.base.connectionManager.ConnectionManager");
        wuType = default("CustomWorldUtility");
        @display("bgi=maps/germany");
        
    submodules: 
        SensorNode[numHosts/3]: SensorNode {
            numHosts = numHosts;
        }
        TempNode[numHosts/3]: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
        }
        
        AllNode[numHosts/3]: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
            hasPressureSensor = true;
            hasHumiditySensor = true;
            hasLightSensor = true;
        }
        
    connections allowunconnected:
}
