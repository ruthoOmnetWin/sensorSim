package sensortechnology.examples.BasicExample;
import sensortechnology.src.SensorNode.Sensor.*;
import sensortechnology.src.SensorNode.*;
import org.mixim.base.modules.BaseNetwork;
import sensortechnology.src.SensorNetworkInterface.BasicWSN;
import sensortechnology.src.SensorNetworkInterface.SensorNetworkInterface;


//
//a network with every kind of node that can be created with the different sensor types
//
network BasicExample extends BasicWSN like SensorNetworkInterface
{
    parameters:
        
        int numEach;
		numHosts = numEach * 5;

    submodules:
        //no sensor
        SensorNode[numEach]: SensorNode {
            numHosts = numHosts;
        }
        //one sensor
        TNode[numEach]: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
        }
        //two sensors
        TPNode[numEach]: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
            hasPressureSensor = true;
        }
        //three sensors
        PHLNode[numEach]: SensorNode {
            numHosts = numHosts;
            hasPressureSensor = true;
            hasHumiditySensor = true;
            hasLightSensor = true;
        }
        //four sensors
        TPHLNode[numEach]: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
            hasPressureSensor = true;
            hasHumiditySensor = true;
            hasLightSensor = true;
        }

    connections allowunconnected:
}
