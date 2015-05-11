package sensortechnology.examples.BasicExample;
import sensortechnology.src.SensorNode.Sensor.*;
import sensortechnology.src.SensorNode.*;
import org.mixim.base.modules.BaseNetwork;
import sensortechnology.src.SensorNetworkInterface.BasicWSN;
import sensortechnology.src.SensorNetworkInterface.SensorNetworkInterface;

network BasicExample extends BasicWSN like SensorNetworkInterface
{
    parameters:
        
		numHosts = 4 * 3;

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
