package sensortechnology.examples.SleepVsNoSleep;
import sensortechnology.src.SensorNode.Sensor.*;
import sensortechnology.src.SensorNode.*;
import org.mixim.base.modules.BaseNetwork;
import sensortechnology.src.SensorNetworkInterface.BasicWSN;
import sensortechnology.src.SensorNetworkInterface.SensorNetworkInterface;

network SleepVsNoSleep extends BasicWSN like SensorNetworkInterface
{
    parameters:
        
		numHosts = 2;

    submodules:
        SleepNode: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
            hasPressureSensor = true;
            hasHumiditySensor = true;
            hasLightSensor = true;
        }
        NoSleepNode: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
            hasPressureSensor = true;
            hasHumiditySensor = true;
            hasLightSensor = true;
        }

    connections allowunconnected:
}
