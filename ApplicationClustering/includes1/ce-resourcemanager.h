#ifndef RES_MANAGER_H
#define RES_MANAGER_H

#include "ce-appstructs.h"
#include "data.h"

// Resources
#define LED1E   0x0001
#define LED1A   0x0002
#define LED2E   0x0004
#define LED2A   0x0004
#define LED3E   0x0010
#define LED3A   0x0020
#define LED4E   0x0040
#define LED4A   0x0080



typedef struct RESOURCE_MAP_ENTRY_STRUCT
{
  unsigned int appId;
  unsigned int resourcesNeed;
  unsigned int resourcesUnique;
  unsigned int energy;
  unsigned char energyOption;
  unsigned char duration;
  unsigned int cpuLoad;
  
} RESOURCE_MAP_ENTRY;



void resourceManagerInit(void);
void resourceManagerCheck(void);
unsigned int resourceManagerAllocate(APP_STRUCT* myAppStruct);
void resourceManagerFree(APP_STRUCT* myAppStruct);
void resourceManagerRequest(PACKET_RESOURCE_REQUEST* myRequestPacket);
void resourceManagerApplicationRequest(PACKET_APPLICATION_REQUEST* myRequestPacket);
#endif

