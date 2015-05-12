package sensortechnology.examples.AllNodes;
import sensortechnology.src.SensorNode.Sensor.*;
import sensortechnology.src.SensorNode.*;
import org.mixim.base.modules.BaseNetwork;
import sensortechnology.src.SensorNetworkInterface.BasicWSN;
import sensortechnology.src.SensorNetworkInterface.SensorNetworkInterface;


//
//a network with every kind of node that can be created with the different sensor types
//
network AllNodes extends BasicWSN like SensorNetworkInterface
{
    parameters:
        
        int numEach = 1;
		numHosts = numEach * 16;

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
		PNode[numEach]: SensorNode {
            numHosts = numHosts;
            hasPressureSensor = true;
        }
        HNode[numEach]: SensorNode {
            numHosts = numHosts;
            hasHumiditySensor = true;
        }
        LNode[numEach]: SensorNode {
            numHosts = numHosts;
            hasLightSensor = true;
        }
        //two sensors
        TPNode[numEach]: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
            hasPressureSensor = true;
        }
        THNode[numEach]: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
            hasHumiditySensor = true;
        }
        TLNode[numEach]: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
            hasLightSensor = true;
        }
        PHNode[numEach]: SensorNode {
            numHosts = numHosts;
            hasPressureSensor = true;
            hasHumiditySensor = true;
        }
        PLNode[numEach]: SensorNode {
            numHosts = numHosts;
            hasPressureSensor = true;
            hasLightSensor = true;
        }
        HLNode[numEach]: SensorNode {
            numHosts = numHosts;
            hasHumiditySensor = true;
            hasLightSensor = true;
        }
        //three sensors
        PHLNode[numEach]: SensorNode {
            numHosts = numHosts;
            hasPressureSensor = true;
            hasHumiditySensor = true;
            hasLightSensor = true;
        }
        THLNode[numEach]: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
            hasHumiditySensor = true;
            hasLightSensor = true;
        }
        TPLNode[numEach]: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
            hasPressureSensor = true;
            hasLightSensor = true;
        }
        TPHNode[numEach]: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
            hasPressureSensor = true;
            hasHumiditySensor = true;
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
