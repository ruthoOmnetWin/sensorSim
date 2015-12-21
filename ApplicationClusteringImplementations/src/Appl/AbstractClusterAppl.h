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

#ifndef ABSTRACTCLUSTERAPPL_H_
#define ABSTRACTCLUSTERAPPL_H_

class AbstractClusterAppl {
public:
    AbstractClusterAppl();
    virtual ~AbstractClusterAppl();

    //all events inside the application layers
    enum ApplClusteringEvents {
        //this event will be the main event used every time sensor should start action
        GET_SENSOR_DATA,
        //types are constant so this should only be called once
        GET_SENSOR_TYPES,
        //this event will be needed to fulfill GET_SENSOR_DATA, because only the nodes with highest res will use their sensors
        GET_BATTERY_RES,
        //this will return the count of events, it is no actual event
        COUNT_EVENTS
    };

    //sensor type enum for communication between the different appl layers
    enum SensorTypes {
        TEMPERATURE_SENSOR_TYPE,
        PRESSURE_SENSOR_TYPE,
        HUMIDITY_SENSOR_TYPE,
        LIGHT_SENSOR_TYPE,
    };

};

#endif /* ABSTRACTCLUSTERAPPL_H_ */
