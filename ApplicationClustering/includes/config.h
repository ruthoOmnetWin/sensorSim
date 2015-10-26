#include "stdio.h"

#define HW_MIXIM

#if !defined (HARDWARE_REVISION_1) &&  !defined (HARDWARE_REVISION_2) && !defined (HW_MIXIM)
    #error "No Hardware defined"
#endif

//defaults
#define MY_NODE_ID  0x0006
#define MY_PAN_ID   0x4444
#define MY_CHANNEL  12
#define SLEEP_CHANNEL  13

#define MEM_NODEID  0x1000
#define MEM_PANID   0x1002

//Broadcast in this PAN (BC = DestinationNode)
#define PAN_BROADCAST   0xFFFF
//Broadcast in all PANs (BC = DestinationNode & DestinationPAN)
#define CHANNEL_BROADCAST 0xFFFF

//time between to WuRX-Forwards (ticks)
#define DEFAULT_WAKEUP_READY_TIME  1000
#define DEFAULT_ALERT_READY_TIME   1000

//duration of CW signal for WuRX (ticks)
#define DEFAULT_WAKEUP_CW_TIME     50



//#define USE_WAKEUP_CHANNEL

//Wakeup-Forwarding (in SleepMode)
//#define USE_WAKEUP_FORWARDING

//Datapacket for Wakeup-Forwarding (in ReceiveMode)
#define USE_WAKEUP_PACKET
