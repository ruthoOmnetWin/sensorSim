package applicationclusteringimplementations;

import org.mixim.base.modules.IBaseApplLayer;

simple CustomDiceApplication like IBaseApplLayer
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
