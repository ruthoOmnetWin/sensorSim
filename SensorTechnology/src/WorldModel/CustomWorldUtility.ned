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

package sensortechnology.src.WorldModel;
import org.mixim.base.modules.BaseWorldUtility;

simple CustomWorldUtility extends BaseWorldUtility
{
    parameters:
        int dataRecreationIntervall = default(0) @unit(s);
        bool createData = default(true);
        bool noisy = default(false);
        int dataGranularity = (10);
        string basePath = default("data/");
        xml xmlTemperature = default(xmldoc("data/temperature.xml"));
        xml xmlPressure = default(xmldoc("data/pressure.xml"));
        xml xmlHumidity = default(xmldoc("data/humidity.xml"));
        xml xmlLight = default(xmldoc("data/light.xml"));
        @class("CustomWorldUtility");
}