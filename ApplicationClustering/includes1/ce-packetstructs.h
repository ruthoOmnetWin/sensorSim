#ifndef PACKET_STRUCTS_H
#define PACKET_STRUCTS_H


#include "typedefs.h"
//#include "data.h"

#define PACKET_TYPE_ROUTING     0x01
#define PACKET_SUBTYPE_DEFAULT  0x00
#define PACKET_TYPE_CONFIG              0x10
#define PACKET_TYPE_STATUS              0x11
#define PACKET_TYPE_DEBUG               0x12
#define PACKET_TYPE_ALERT               0x13
#define PACKET_TYPE_EVENT               0x14
#define PACKET_TYPE_NODE_REQUEST        0x15
#define PACKET_TYPE_NODE_RESPONSE       0x16



#define PACKET_TYPE_CMD_SLEEP           0x30
#define PACKET_TYPE_CMD_DATA            0x31
#define PACKET_TYPE_CMD_EXPLORE         0x32
#define PACKET_TYPE_CMD_WAKEUP          0x33

#define PACKET_TYPE_EXP_RESP_0X40       0x40
#define PACKET_TYPE_EXP_RESP_0X41       0x41
#define PACKET_TYPE_EXP_RESP_0X43       0x43
#define PACKET_TYPE_EXP_RESP_0X47       0x47

#define PACKET_TYPE_APP                 0x50
#define PACKET_TYPE_APP_REQUEST         0x51
#define PACKET_TYPE_APP_RESPONSE        0x52
#define PACKET_TYPE_APP_EXECUTE         0x53
#define PACKET_TYPE_APP_SUSPEND         0x54
#define PACKET_TYPE_APP_STOP            0x55
#define PACKET_TYPE_APP_UPDATE          0x56
#define PACKET_TYPE_APP_MASTER_1ST_EVENT  0x57
#define PACKET_TYPE_APP_MASTER_EVENT    0x58

#define PACKET_TYPE_APP_MASTER_REQUEST  0x59
#define PACKET_TYPE_APP_MASTER_SET      0x5A

#define PACKET_TYPE_RESOURCE_REQUEST    0x60
#define PACKET_TYPE_RESOURCE_RESPONSE   0x61

#define PACKET_SUBTYPE_APP_NONE         0x00
#define PACKET_SUBTYPE_APP_DELETE_1     0x01
#define PACKET_SUBTYPE_APP_STOP_DEL_1   0x02
#define PACKET_SUBTYPE_APP_DELETE_2     0x03
#define PACKET_SUBTYPE_APP_STOP_DEL_2   0x04

#define PACKET_SUBTYPE_APP_SUSPEND      0x05
#define PACKET_SUBTYPE_APP_RESUME       0x06
#define PACKET_SUBTYPE_APP_REQUEST      0x07

#define RESPONSE_FAIL                   0x01
#define RESPONSE_OK                     0x02

#define RESPONSE_DELETED                0x10
#define RESPONSE_SUSPENDED              0x11
#define RESPONSE_STARTED                0x12
#define RESPONSE_MARKED                 0x13
#define RESPONSE_RESOURCE_ERROR         0x14


#define RESPONSE_NO_APPLICATON          0x00
#define RESPONSE_HARDWARE_IN_USE        0x01
#define RESPONSE_LOW_ENERGY             0x02
#define RESPONSE_OK_VALUE               0x04




#define OPTIONS_MASTER_INFORMATION      0x01




#define PACKET_SUBTYPE_ALL_CHILDS 0x01
//#define PACKET_SUBTYPE_GO_SLEEP   0x02
//#define PACKET_SUBTYPE_DONT_SLEEP 0x04

#define PACKET_

#define DEFAULT_TTL               0x20

#define HEADERSIZE 8

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

typedef struct _PACKET_MASTER_ENTRY
{
  unsigned short appMasterId;
  unsigned short value;
} PACKET_MASTER_ENTRY;

typedef struct _PACKET_APPLICATION_STRUCT_
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__
  //---------PAYLOAD-------------
   unsigned char id;            // internal id  //=> useless
   unsigned char count;         // how often // 0=>endless, 1=> one time,  ...
   unsigned char appId;         // id application (local) 
   unsigned char storage;       // id application (local)
   unsigned int  parameterA;     // optional info/parameter
   unsigned int  parameterB;     // optional info/parameter
   unsigned long start;         // first start point (can be zero)
   unsigned long delay;         // delay until next execution
   unsigned char options;
   unsigned char cdummy;
   unsigned char idummy;

} PACKET_APPLICATION;


typedef struct _PACKET_APPLICATION_MASTER_1ST_EVENT_STRUCT
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__
  //---------PAYLOAD-------------
   unsigned int event;      // yes/no/temporary/...
   unsigned int random;     // reference at appMaster
   unsigned long timestamp; //
} PACKET_APPLICATION_MASTER_1ST_EVENT;

typedef struct _PACKET_EVENT_STRUCT
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__
  //---------PAYLOAD-------------
   unsigned int event;      // yes/no/temporary/...
   unsigned int random;     // reference at appMaster
   unsigned long timestamp; //
} PACKET_EVENT;


typedef struct _PACKET_APPLICATION_MASTER_EVENT_STRUCT
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__
  //---------PAYLOAD-------------
   unsigned int event;      // yes/no/temporary/...
   unsigned int random;     // reference at appMaster
   unsigned long timestamp; //
   PACKET_MASTER_ENTRY masterEntries[20];
} PACKET_APPLICATION_MASTER_EVENT;

typedef struct _PACKET_APPLICATION_REQUEST_STRUCT_
{
  //---------HEADER--------------<
    __GENERIC_PACKET_HEADER__
  //---------PAYLOAD-------------
   unsigned int application;    // code of application
   unsigned int reference;      // reference at appMaster
   unsigned int request;    // id application (local)
   unsigned int value;    // id application (local)
} PACKET_APPLICATION_REQUEST;


typedef struct _PACKET_APPLICATION_UPDATE_STRUCT_
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__   //subid == action
  //---------PAYLOAD-------------
   unsigned int application;    // code of application
   unsigned int reference;      // reference at appMaster
   unsigned int update;         // action
   unsigned int dummy;
   
} PACKET_APPLICATION_UPDATE;

typedef struct _NODE_ENTRY_STRUCT
{
  unsigned int nodeId;
  unsigned int value;
  unsigned int reference;
  unsigned int dummy;
} NODE_ENTRY;

typedef struct _PACKET_APPLICATION_MASTER_REQUEST_
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__
   unsigned int application;        // reference at appMaster
   unsigned int reference;      // yes/no/temporary/...
   unsigned long timestamp; //
   NODE_ENTRY nodeEntries[10];
  //---------PAYLOAD-------------

} PACKET_APPLICATION_MASTER_REQUEST;


typedef struct _PACKET_APPLICATION_RESPONSE_STRUCT
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__
  //---------PAYLOAD-------------
   unsigned int response;      // yes/no/temporary/...
   unsigned int reference;     // reference at appMaster
   unsigned char appId;        // id application (local)
   unsigned char storage;      // 
   unsigned int dummy;         //
} PACKET_APPLICATION_RESPONSE;



typedef struct _REQUEST_ENTRY_STRUCT
{
  unsigned char reqId;
  unsigned char reqOption;
  unsigned int  reqObject;
} REQUEST_ENTRY;

typedef struct _PACKET_RESOURCE_REQUEST_STRUCT
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__   //subid == action
  //---------PAYLOAD-------------
   unsigned int application;    // code of application
   unsigned int reference;      // reference at appMaster
   unsigned int masterId;       //dummy ?
   unsigned char options;       // 0x01->keine
   unsigned char priority;      //dummy?
   REQUEST_ENTRY requestEntry[20];
} PACKET_RESOURCE_REQUEST;


typedef struct _PACKET_RESOURCE_RESPONSE_STRUCT
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__   //subid == action
  //---------PAYLOAD-------------
   unsigned int application;    // code of application
   unsigned int reference;      // reference at appMaster
   unsigned int masterId;       //dummy ?
   unsigned int value;          //
   unsigned int valuesEntry[20];
} PACKET_RESOURCE_RESPONSE;


typedef struct _GENERIC_PACKET_STRUCT
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__
  //---------PAYLOAD-------------
   unsigned char data[100];
} GENERIC_PACKET;


typedef struct _DEBUG_PACKET_STRUCT
{
  //---------HEADER--------------
    __GENERIC_PACKET_HEADER__
  //---------PAYLOAD-------------
   unsigned char mode;
   unsigned char dummy;
   unsigned short dummy2;
} DEBUG_PACKET;



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



#endif
