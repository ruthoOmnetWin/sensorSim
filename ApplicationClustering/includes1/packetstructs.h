#ifndef PACKET_STRUCTS_H
#define PACKET_STRUCTS_H


#include "typedefs.h"
//#include "data.h"

#define PACKET_TYPE_ROUTING     0x01
#define PACKET_SUBTYPE_DEFAULT  0x00
#define PACKET_TYPE_CONFIG      0x10
#define PACKET_TYPE_STATUS      0x11
#define PACKET_TYPE_DEBUG       0x12
#define PACKET_TYPE_ALERT       0x13



#define PACKET_TYPE_DATA          0x20  //2x -> Data , x ist Priorit#t


#define PACKET_TYPE_CMD_SLEEP     0x30
#define PACKET_TYPE_CMD_DATA      0x31
#define PACKET_TYPE_CMD_EXPLORE   0x32
#define PACKET_TYPE_CMD_WAKEUP    0x33

#define PACKET_TYPE_EXP_RESP_0X40    0x40
#define PACKET_TYPE_EXP_RESP_0X41    0x41
#define PACKET_TYPE_EXP_RESP_0X43    0x43
#define PACKET_TYPE_EXP_RESP_0X47    0x47

#define PACKET_TYPE_APP           0x50
#define PACKET_TYPE_APP_REQ       0x51
#define PACKET_TYPE_APP_RESP      0x52
#define PACKET_TYPE_APP_CMD       0x53


#define PACKET_SUBTYPE_ALL_CHILDS 0x01
//#define PACKET_SUBTYPE_GO_SLEEP   0x02
//#define PACKET_SUBTYPE_DONT_SLEEP 0x04

#define PACKET_

#define DEFAULT_TTL               0x20



#define __GENERIC_PACKET_HEADER__ \
    unsigned char packetType; \
    unsigned char subType;    \
    unsigned char ttl;        \
    unsigned char payloadsize;\
    unsigned short srcId;     \
    unsigned short dstId;
typedef struct _PACKET_ENTRY
{
  unsigned short nodeId;
  unsigned short parrentId;
} PACKET_ENTRY;


typedef struct _ROUTING_INFO
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__
  //---------PAYLOAD-------------
   unsigned char options;        // Options: 
   unsigned char distance;            // ???
   unsigned short dataDestination;
//  //---------Routing Entries PAYLOAD-------------
   PACKET_ENTRY packetEntry[20];
} ROUTING_INFO;

typedef struct _MESUREMENT_DATASET_
{
   unsigned long timestamp;
   unsigned short voltage;
   unsigned short temperatureInternal;   
   unsigned short temperatureExternal;
   unsigned short voltageMST;
   unsigned short voltageLPA;
   unsigned short voltageFRI;
   
} MESUREMENT_DATASET;


typedef struct _GENERIC_PACKET_STRUCT
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__
  //---------PAYLOAD-------------
   unsigned char data[100];
} GENERIC_PACKET;


typedef struct _CMD_SLEEP_PACKET_STRUCT__
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__
  //---------PAYLOAD-------------
   unsigned short command;
   unsigned short sleepMode;
} CMD_SLEEP_PACKET;

typedef struct _ALERT_PACKET_STRUCT__
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__
  //---------PAYLOAD-------------
   unsigned long  timestamp;
   unsigned short nodeId;
   unsigned char alertId;
   unsigned char dummy;
} ALERT_PACKET;

typedef struct _DEBUG_PACKET_STRUCT__
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__
  //---------PAYLOAD-------------
   unsigned char mode;
   unsigned char dummy;
   unsigned short dummy2;
} DEBUG_PACKET;


typedef struct _CMD_DATA_PACKET_STRUCT__
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__
  //---------PAYLOAD-------------
   unsigned short destination;
   unsigned char count;
   unsigned char state;  //SleepModes
} CMD_DATA_PACKET;

typedef struct _GENERIC_PACKET_TX_STRUCT
{
/* --- TX Struct --------------------------------------- */
   unsigned short txDstId;
   unsigned short txDstPan;
   unsigned char txOptions;
   unsigned char txSize;
   unsigned short dummy;
/* --- Generic Packet Struct ---------------------------- */
   GENERIC_PACKET genericPacket;
} GENERIC_PACKET_TX;

typedef struct _GENERIC_PACKET_RX_STRUCT
{
/* --- RX Struct --------------------------------------- */
   unsigned short rxSrcId;
   unsigned short rxDstPan;
   unsigned char rxRssi;
   unsigned char rxSize;
   unsigned short dummy;
/* --- Generic Packet Struct ---------------------------- */
   GENERIC_PACKET genericPacket;
} GENERIC_PACKET_RX;


typedef struct _DATASET_PACKET_STRUCT
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__
  //---------PAYLOAD-------------
    MESUREMENT_DATASET datasets[8];
} DATASET_PACKET;


#endif
