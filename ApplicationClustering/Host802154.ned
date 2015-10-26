package applicationClustering;

import org.mixim.modules.node.WirelessNodeBatteryPlusTran;

module Host802154 extends WirelessNodeBatteryPlusTran
{
    parameters:
        arpType       = "ArpHost";
        nicType       = "Nic802154_TI_CC2420A";
        //transportType = "Aggregation";
        networkType = "NetworkLayer2";
}
