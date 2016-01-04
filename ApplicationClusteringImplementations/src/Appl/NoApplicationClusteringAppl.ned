package applicationclusteringimplementations.Appl;

import org.mixim.base.modules.IBaseApplLayer;

//
// TODO auto-generated type
//
simple NoApplicationClusteringAppl extends CustomDiceApplication like IBaseApplLayer
{
    parameters:
        int sendingIntervall @unit("s");
        int wakeupIntervall @unit("s");
        
        @class(NoApplicationClusteringAppl);
    gates:
}
