package sensortechnology.examples.SleepOutOfSync;
import sensortechnology.src.SensorNode.Sensor.*;
import sensortechnology.src.SensorNode.*;
import org.mixim.base.modules.BaseNetwork;
import sensortechnology.src.SensorNetworkInterface.BasicWSN;
import sensortechnology.src.SensorNetworkInterface.SensorNetworkInterface;


//
//a network that shows different nodes with different day-time-routines
//
network SleepOutOfSync extends BasicWSN like SensorNetworkInterface
{
    parameters:
        
        int numEach;
		numHosts = numEach * 5;

    submodules:
        //two sensors
        TPNode1[numEach]: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
            hasPressureSensor = true;
        }
        TPNode2[numEach]: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
            hasPressureSensor = true;
        }

    connections allowunconnected:
}
