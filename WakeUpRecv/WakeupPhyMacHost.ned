package wakeuprecv;

import inet.base.NotificationBoard;
import org.mixim.base.modules.BaseBattery;
import org.mixim.examples.analogueModels.SamplePhyLayer;
import org.mixim.examples.ieee802154Narrow.WorldUtilityStats;
import org.mixim.modules.mac.AlohaMacLayer;
import org.mixim.modules.nic.Nic80211MultiChannel;
import org.mixim.modules.nic.Nic802154_TI_CC2420;
import org.mixim.modules.node.WirelessNodeBatteryNetwl;
import org.mixim.modules.phy.PhyLayer;
import org.mixim.modules.power.battery.SimpleBattery;
import org.mixim.modules.transport.Aggregation;


module WakeupPhyMacHost extends WirelessNodeBatteryNetwl
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

//        primaryNet.upperGateOut --> appl.primaryDataIn;
//        primaryNet.upperGateIn <-- appl.primaryDataOut;
//        primaryNet.upperControlOut --> { @display("ls=red;m=m,70,0,70,0"); } --> appl.primaryControlIn;
//        primaryNet.upperControlIn <-- { @display("ls=red;m=m,70,0,70,0"); } <-- appl.primaryControlOut;

//        primaryNic.upperGateOut --> primaryNet.lowerGateIn;
//        primaryNic.upperGateIn <-- primaryNet.lowerGateOut;
//        primaryNic.upperControlOut --> { @display("ls=red;m=m,70,0,70,0"); } --> primaryNet.lowerControlIn;
//        primaryNic.upperControlIn <-- { @display("ls=red;m=m,70,0,70,0"); } <-- primaryNet.lowerControlOut;

}

