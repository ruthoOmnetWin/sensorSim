#ifndef APP_SCHEDULER_H
#define APP_SCHEDULER_H

#include "ce-appstructs.h"

void appschedulerInit(void);
void appschedulerCalcNextExecution(APP_STRUCT* myAppStruct);
void appschedulerUpdatePosition(APP_STRUCT* myAppStruct);
void appschedulerInsertPosition(APP_STRUCT* myAppStruct);
void appschedulerRemoveApp(APP_STRUCT* myAppStruct);
void appschedulerUpdateFirstApp(void);

unsigned int appschedulerInsertAppEntry(
    unsigned char appId,unsigned char status,unsigned int master,
    unsigned char count,unsigned long delay,unsigned long start,
    unsigned int parameterA,unsigned int parameterB,unsigned char options);


enum APP_SCHEDULE_STATES
{
    APP_STATE_NONE = 0,
    APP_STATE_CHECK,
    APP_STATE_INIT,
    APP_STATE_READY,
    APP_STATE_EXIT,
    APP_STATE_DONE,
    APP_STATE_SUSPEND,
    APP_STATE_SUSPENDED,
    APP_STATE_REMOVE,
    APP_STATE_DELETED,
    APP_STATE_RESERVED
};



#endif

