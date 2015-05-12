package sensortechnology.examples.TrafficGenExample;
import sensortechnology.src.SensorNode.Sensor.*;
import sensortechnology.src.SensorNode.*;
import org.mixim.base.modules.BaseNetwork;
import sensortechnology.src.SensorNetworkInterface.BasicWSN;
import sensortechnology.src.SensorNetworkInterface.SensorNetworkInterface;

//
//module with a lot of traffic
//it uses the module TrafficGen
//
network TrafficGenExample extends BasicWSN like SensorNetworkInterface
{
    parameters:
        
		numHosts = 9;

    submodules:
        SensorNode[numHosts/3]: SensorNode {
            numHosts = numHosts;
        }
        TempNode[numHosts/3]: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
            hasLightSensor = true;
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
