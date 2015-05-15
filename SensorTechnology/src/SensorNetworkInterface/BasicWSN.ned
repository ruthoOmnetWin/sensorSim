//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package sensortechnology.src.SensorNetworkInterface;

import org.mixim.base.connectionManager.IConnectionManager;
import org.mixim.base.modules.IWorldUtility;
import sensortechnology.src.WorldModel.CustomWorldUtility;

//
//network with the needed parameters for the use of the sensor implementation
//
network BasicWSN
{
    parameters:
        int numHosts;        
        
        bool createData = default(false);
        bool noisyWorld = default(false);
        world.basePath = "data/";
        world.xmlTemperature = xmldoc("data/temperature.xml");
        world.xmlPressure = xmldoc("data/pressure.xml");
        world.xmlHumidity = xmldoc("data/humidity.xml");
		world.xmlLight = xmldoc("data/light.xml");
        
        double playgroundSizeX @unit(m); // x size of the area the nodes are in (in meters)
        double playgroundSizeY @unit(m); // y size of the area the nodes are in (in meters)
        double playgroundSizeZ @unit(m); // z size of the area the nodes are in (in meters)
        **.mobility.constraintAreaMinX = default(0m);
        **.mobility.constraintAreaMinY = default(0m);
        **.mobility.constraintAreaMinZ = default(0m);
        **.mobility.constraintAreaMaxX = default(playgroundSizeX);
        **.mobility.constraintAreaMaxY = default(playgroundSizeY);
        **.mobility.constraintAreaMaxZ = default(playgroundSizeZ);
        string cmType = default("org.mixim.base.connectionManager.ConnectionManager"); // connection manager to use
        string wuType = default("org.mixim.base.modules.CustomWorldUtility");            // world utility to use

        @display("bgb=$playgroundSizeX,$playgroundSizeY,white;bgp=0,0");

    submodules:
        connectionManager: <cmType> like IConnectionManager {
            parameters:
                @display("p=201,0;i=abstract/multicast;is=s");
        }
        world: CustomWorldUtility {
            parameters:
                playgroundSizeX = playgroundSizeX;
                playgroundSizeY = playgroundSizeY;
                playgroundSizeZ = playgroundSizeZ;
                @display("p=280,0;i=misc/globe;is=s");
                noisy = noisyWorld;
                createData = createData;
        }
    connections allowunconnected:
}
