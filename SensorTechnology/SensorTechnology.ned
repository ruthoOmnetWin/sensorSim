package sensortechnology; 
import sensortechnology.src.SensorNode.Sensor.*;
import sensortechnology.src.SensorNode.*;

import org.mixim.base.modules.BaseNetwork;

network SensorTechnology extends BaseNetwork
{
    parameters:
        int numHosts = 10;
        world.createData = true;
        int test = 0;
        
        cmType = default("org.mixim.base.connectionManager.ConnectionManager");
        wuType = default("CustomWorldUtility");
        
    submodules: 
        SensorNode[numHosts/2]: AbstractSensorNode {
            numHosts = numHosts;
        }
        TempNode[numHosts/2]: AbstractSensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
        }
        
    connections allowunconnected:
}
