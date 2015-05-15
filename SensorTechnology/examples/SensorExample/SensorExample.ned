package sensortechnology.examples.SensorExample;
import sensortechnology.src.SensorNode.Sensor.*;
import sensortechnology.src.SensorNode.*;
import org.mixim.base.modules.BaseNetwork;
import sensortechnology.src.SensorNetworkInterface.BasicWSN;
import sensortechnology.src.SensorNetworkInterface.SensorNetworkInterface;


network SensorExample extends BasicWSN like SensorNetworkInterface
{
    parameters:
        
        numHosts = 1;

    submodules:
        TNode: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
            noisy = true;
        }

    connections allowunconnected:
}
