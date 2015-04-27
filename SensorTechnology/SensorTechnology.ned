package sensortechnology; 
import sensortechnology.src.SensorNode.Sensor.*;
import sensortechnology.src.SensorNode.*;

import org.mixim.base.modules.BaseNetwork;

network SensorTechnology extends BaseNetwork
{
    parameters:
        int numHosts = 1;
        world.createData = false;
        
        cmType = default("org.mixim.base.connectionManager.ConnectionManager");
        wuType = default("CustomWorldUtility");
        @display("bgi=maps/germany");
        
    submodules: 
        SensorNode[0]: AbstractSensorNode {
            numHosts = numHosts;
        }
        TempNode[0]: AbstractSensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
        }
        AllNode[numHosts]: AbstractSensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
            hasPressureSensor = true;
            hasHumiditySensor = true;
            hasLightSensor = true;
        }
        
    connections allowunconnected:
}
