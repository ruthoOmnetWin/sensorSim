package sensortechnology;
import sensortechnology.src.SensorNode.Sensor.*;
import sensortechnology.src.SensorNode.*;
import org.mixim.base.connectionManager.IConnectionManager;
import sensortechnology.src.WorldModel.CustomWorldUtility;

network SensorTechnologyHost802154
{
    parameters:
        string cmType = default("org.mixim.base.connectionManager.ConnectionManager");
        string wuType = default("CustomWorldUtility");
        bool createNewEnvironmentData = false;

        double playgroundSizeX @unit(m); // x size of the area the nodes are in (in meters)
        double playgroundSizeY @unit(m); // y size of the area the nodes are in (in meters)
        double playgroundSizeZ @unit(m); // z size of the area the nodes are in (in meters)
        **.mobility.constraintAreaMinX = default(0m);
        **.mobility.constraintAreaMinY = default(0m);
        **.mobility.constraintAreaMinZ = default(0m);
        **.mobility.constraintAreaMaxX = default(playgroundSizeX);
        **.mobility.constraintAreaMaxY = default(playgroundSizeY);
        **.mobility.constraintAreaMaxZ = default(playgroundSizeZ);
        **.battery.numDevices = 4 * 1;
        @display("bgi=maps/germany,bgb,$playgroundSizeX,$playgroundSizeY,white;bgp=0,0;bgb=403,503");

    submodules:
        SensorNode: Host802154_2400MHzSensorNode {
            numHosts = 1;
        	**.notAffectedByHostState= true;
            @display("p=300,51");
        }
        connectionManager: <cmType> like IConnectionManager {
            parameters:
                @display("i=abstract/multicast;is=s");
        }
        world: CustomWorldUtility {
            //for every sensor (NOT only every node) there is one gate needed
            createData = createNewEnvironmentData;
        }
    connections allowunconnected:
}
