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
        
        //int numEach;
		//numHosts = numEach * 2;
		numHosts = 2;

    submodules:
        //two sensors
        TNode1: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
        }
        TNode2: SensorNode {
            numHosts = numHosts;
            hasTemperatureSensor = true;
        }

    connections allowunconnected:
}
