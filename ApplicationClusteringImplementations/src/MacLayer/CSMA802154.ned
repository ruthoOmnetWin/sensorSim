package applicationclusteringimplementations.MacLayer;
import org.mixim.modules.mac.csma;


simple CSMA802154HostStateHandled extends csma
{
    parameters:
        @class(CSMA802154HostStateHandled);
        
        headerLength @unit(bit) = default(72 bit);
        macMaxCSMABackoffs = default(4);  // takes values between 0 and 5  
        //txPower @unit(mW);
        useMACAcks = default(true);
        
        backoffMethod = "exponential";
        macMaxBE = default(5);	// takes values between 3 and 8
        macMinBE = default(3);	// takes values between 0 and macMaxBE
}
