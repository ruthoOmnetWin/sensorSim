package applicationClustering;

import inet.base.NotificationBoard;
import org.mixim.modules.application.SensorApplLayer;
import org.mixim.modules.node.WirelessNodeBatteryNetwl;
import org.mixim.modules.power.battery.SimpleBattery;

module DicePhyMacHost extends WirelessNodeBatteryNetwl
{
    parameters:
        networkType = "NetworkLayer2";
        nicType = "Nic802154_TI_CC2420A";
        //mobilityType = "StationaryMobility";
        //nicType = "Nic802154A";
        arpType = "ArpHost";
        int numHosts; // total number of hosts in the network
    types:
    submodules:
    connections allowunconnected:
}

