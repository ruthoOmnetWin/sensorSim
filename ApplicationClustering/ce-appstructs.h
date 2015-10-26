#ifndef APP_STRUCTS_H
#define APP_STRUCTS_H


#include "typedefs.h"

#define EVENT_APP_MANAGER      0x01



typedef struct _APP
{
   unsigned char id;            // internal id
   unsigned char appId;         // id application (local)
   unsigned char status;        // enable,executed,...   0x00 -> emtpy Struct
   unsigned char count;         // how often // 0=>endless, 1=> one time,  ...

   unsigned char meta;
   unsigned char options;       //bit 0 => Info an Master
   unsigned int  master;        //master of this app

   unsigned int  parameterA;     // optional info/parameter
   unsigned int  parameterB;     // optional info/parameter

   unsigned long start;         // first start point (can be zero)
   unsigned long delay;         // delay until next execution

   //unsigned long nextstart;     // calc

   void* nextAppStruct;
   void* lastAppStruct;
} APP_STRUCT;


extern APP_STRUCT* appFirstEntry;
extern APP_STRUCT* appNextEntry;

#define APP_LISTCOUNT  50
extern  APP_STRUCT appList[APP_LISTCOUNT];

enum APPLICATIONS
{
    NONE = 0,
    LED1_EIN = 0x81,
    LED1_AUS,
    LED2_EIN,
    LED2_AUS,
    LED3_EIN,
    LED3_AUS,
    LED4_EIN,
    LED4_AUS,
    META_LED1_FLASH,
    META_LED2_FLASH,
    META_LED3_FLASH,
    META_LED4_FLASH,
    META_NEIGHBOURS
};

#endif
