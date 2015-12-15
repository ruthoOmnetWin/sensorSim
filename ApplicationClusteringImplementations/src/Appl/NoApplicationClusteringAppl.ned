package applicationclusteringimplementations.Appl;

import org.mixim.base.modules.IBaseApplLayer;

//
// TODO auto-generated type
//
simple NoApplicationClusteringAppl like IBaseApplLayer
{
    parameters:
        int headerLength @unit("bit"); // length of the application message header (in bits)
        int coordinatorNodeAddr;
        int sendingIntervall @unit("s");
        
        @class(NoApplicationClusteringAppl);
    gates:
        input lowerLayerIn; // from network layer
        output lowerLayerOut; // to network layer
        input lowerControlIn; // control from network layer
        output lowerControlOut; // control to network layer
}
