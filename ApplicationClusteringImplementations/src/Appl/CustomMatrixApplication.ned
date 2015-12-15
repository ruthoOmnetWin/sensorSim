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

package applicationclusteringimplementations.Appl;

import org.mixim.base.modules.IBaseApplLayer;

simple CustomMatrixApplication like IBaseApplLayer
{
    parameters:
        bool   debug = default(false); // debug switch
        bool   stats = default(false);   // stats switch
        bool   trace = default(false); // trace switch
        double nodeAddr;        // node address
		double coordinatorNodeAddr;		// packet destination node address
    	int    headerLength @unit("bit");   // length of the application message header (in bits)

    gates:
        input lowerLayerIn; // to receive data from communications stack
        output lowerLayerOut; // to send data to communications stack
        input lowerControlIn; // to receive control messages from communications stack
        output lowerControlOut; // to send  control messages from communications stack

}
