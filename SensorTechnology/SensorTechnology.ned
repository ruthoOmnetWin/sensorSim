package sensortechnology; 
import sensortechnology.src.SensorNode.Sensor.*;
import sensortechnology.src.SensorNode.*;

import org.mixim.base.modules.BaseNetwork;

network SensorTechnology extends BaseNetwork
{
    parameters:
        SensorNode[0].hasTemperatureSensor = true;
        SensorNode[1].hasPressureSensor = true;
        SensorNode[1].hasTemperatureSensor = true;
        int numHosts = 10;
        world.createData = false;
        
        cmType = default("org.mixim.base.connectionManager.ConnectionManager");
        wuType = default("CustomWorldUtility");
        
    submodules: 
        SensorNode[numHosts]: AbstractSensorNode {
            numHosts = numHosts;
        }
        
    connections allowunconnected:
}
