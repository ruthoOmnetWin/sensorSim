//
// Generated file, do not edit! Created by opp_msgc 4.3 from GenericPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include "ce-data.h"
#include "ce-clusterApplication.h"


unsigned int MYCLASS appschedulerInsertAppEntry(unsigned char appId, unsigned char status,
        unsigned int master, unsigned char count, unsigned long delay, unsigned long start, unsigned int parameterA,
        unsigned int parameterB, unsigned char options)
{
    APP_STRUCT* myAppStruct;
    unsigned int i;
    for (i = 0; i < APP_LISTCOUNT; i++)
    {
        if (appList[i].status == APP_STATE_NONE || appList[i].status == APP_STATE_DELETED)
        {
            appList[i].status = status;
            appList[i].id = i;
            appList[i].appId = appId;
            appList[i].count = count;
            appList[i].delay = delay;
            appList[i].start = start;
            appList[i].meta = 0;
            appList[i].parameterA = parameterA;
            appList[i].parameterB = parameterB;
            appList[i].options = options;
            appList[i].master = master;
            myAppStruct = &appList[i];
            break;
        }
    }
    if (i >= APP_LISTCOUNT)  //App-Limit
    {
        return -1;
    }
    //i = sizeof(myAppStruct);
    if (myAppStruct->status == APP_STATE_INIT)
    {
        appschedulerCalcNextExecution(myAppStruct);
        appschedulerInsertPosition(myAppStruct);
    }
    return i;
}

void MYCLASS appschedulerUpdateApp(APP_STRUCT* myAppStruct)
{
    appschedulerRemoveApp(myAppStruct);
    if (myAppStruct->status == APP_STATE_INIT || myAppStruct->status == APP_STATE_READY)
        appschedulerInsertPosition(myAppStruct);
}

// after execution of a app to update all
void MYCLASS appschedulerUpdateFirstApp(void)
{
    APP_STRUCT* myAppStructTmp = appFirstEntry;
    if (appFirstEntry == NULL)
    {
        //remove schedule timer
        clusterApplicationUpdateTimer(TIMER_ID_APPLICATION_SCHEDULER, TIMER_TYPE_DELETE, 0);
        return;
    }
/*
    if (appFirstEntry->count > 0)
    {
        if (appFirstEntry->meta == 0)
        {
            appFirstEntry->count--;
        }
    }
*/

    if (appFirstEntry->meta==0)  // this was the last execution
    {
        if (appFirstEntry->count == 0)
        {
            appFirstEntry->status = APP_STATE_REMOVE;
            globalEvents |= EVENT_APP_MANAGER;
            if (appFirstEntry->nextAppStruct == NULL)
            {
                //clear timer
                clusterApplicationUpdateTimer(TIMER_ID_APPLICATION_SCHEDULER, TIMER_TYPE_DELETE, 0);
                return;

            }
        }
        else
        {

        }
    }


    if (appFirstEntry->nextAppStruct != NULL)
    {
        appFirstEntry = (APP_STRUCT*) appFirstEntry->nextAppStruct;
        appFirstEntry->lastAppStruct = NULL;

        myAppStructTmp->nextAppStruct = NULL;
        myAppStructTmp->lastAppStruct = NULL;
        if (myAppStructTmp->status == APP_STATE_INIT || myAppStructTmp->status == APP_STATE_READY)
            appschedulerInsertPosition(myAppStructTmp);

        //setting the timer
    }

    clusterApplicationUpdateTimer(TIMER_ID_APPLICATION_SCHEDULER, TIMER_TYPE_SET, appFirstEntry->start);

    //

}

void MYCLASS appschedulerRemoveApp(APP_STRUCT* myAppStruct)
{
    APP_STRUCT* appStructTmp = appFirstEntry;
    if (appFirstEntry == NULL)
        return;
    myAppStruct->status = APP_STATE_REMOVE;
    do
    {
        if (myAppStruct == appStructTmp) //found
        {
            //Head
            if (appFirstEntry == appStructTmp)
            {
                appFirstEntry = (APP_STRUCT*) myAppStruct->nextAppStruct;
                appFirstEntry->lastAppStruct = NULL;
            }
            //Tail
            else if (appStructTmp->nextAppStruct == NULL)
            {
                (((APP_STRUCT*) (myAppStruct->lastAppStruct))->nextAppStruct) = NULL;
            }
            else
            {
                //forward link - last element to next element
                (((APP_STRUCT*) (myAppStruct->lastAppStruct))->nextAppStruct) = myAppStruct->nextAppStruct;
                //backward link - next element to last element
                (((APP_STRUCT*) (myAppStruct->nextAppStruct))->lastAppStruct) = myAppStruct->lastAppStruct;
            }
            break;
            //AppStatus -> suspend

        }
        appStructTmp = (APP_STRUCT*) appStructTmp->nextAppStruct;
    } while (appStructTmp != NULL);

    globalEvents |= EVENT_APP_MANAGER;  //delete this and release resources by appmanager

    //myAppStruct->status = APP_STATE_DELETED;
}

// Calculate the next execution timestamp for one specific application entry
void MYCLASS appschedulerCalcNextExecution(APP_STRUCT* myAppStruct)
{
    volatile long t = ticks; //ticks maybe changed in calculations
    //unsigned long nextstart = (t + myAppStruct->start) - (t % myAppStruct->delay);

    unsigned long nextstart = myAppStruct->start + myAppStruct->delay;

    if (myAppStruct->start > ticks)
    {
        return;  //execution is in the future ==>  OK
    }
    if (nextstart > ticks)
    {
        myAppStruct->start = nextstart;  //wait delay, then execution is in the future ==>  OK
        return;
    }

    //check for modulo 0 !!
    if (myAppStruct->delay==0)
    {
        myAppStruct->start = t+1;
    }
    else
    {
        nextstart = t + myAppStruct->delay - ((t - myAppStruct->start) % myAppStruct->delay);
        myAppStruct->start = nextstart;
    }
    //berechne nexte ausführung

}

void MYCLASS appschedulerInsertPosition(APP_STRUCT* myAppStruct)
{
    APP_STRUCT* appStructTmp = appFirstEntry;
    if (myAppStruct->status == APP_STATE_INIT)
        myAppStruct->status = APP_STATE_READY;

    if (appFirstEntry == NULL)  //first entry ==> head
    {
        appFirstEntry = myAppStruct;
        myAppStruct->nextAppStruct = NULL;
        myAppStruct->lastAppStruct = NULL;
        appschedulerUpdateFirstApp();
        return;
    }

    do
    {
        if (myAppStruct->start < appStructTmp->start)
        {

            // TODO: dont point to myself

            if (appStructTmp == appFirstEntry)
            {
                appFirstEntry = myAppStruct;
                appStructTmp->lastAppStruct = myAppStruct;
                myAppStruct->nextAppStruct = appStructTmp;
                myAppStruct->lastAppStruct = NULL; // optional
                appschedulerUpdateFirstApp();
            }
            else
            {

                // TODO: dont point to myself

                //update pointer (last element to inserted (forward))
                (((APP_STRUCT*) (appStructTmp->lastAppStruct))->nextAppStruct) = myAppStruct;

                //update pointer (inserted object)
                myAppStruct->lastAppStruct = appStructTmp->lastAppStruct;
                myAppStruct->nextAppStruct = appStructTmp;

                //update pointer (next element to inserted (revers))
                appStructTmp->lastAppStruct = myAppStruct;
            }
            break;
        }
        else if (appStructTmp->nextAppStruct == NULL) // last position (tail) --> append
        {
            appStructTmp->nextAppStruct = myAppStruct;
            myAppStruct->nextAppStruct = NULL; // optional
            myAppStruct->lastAppStruct = appStructTmp;
            break;
        }
        appStructTmp = (APP_STRUCT*) appStructTmp->nextAppStruct;
    } while (appStructTmp != NULL);

}

void MYCLASS appschedulerInit(void)
{
    int i;
    //ClearList
    appFirstEntry = NULL;

    //Set pointers in whole list (empty list)
    for (i = 0; i < APP_LISTCOUNT; i++)
    {
        APP_STRUCT* myAppStructNow = &appList[i];
        myAppStructNow->id = 0;
        myAppStructNow->appId = 0;
        myAppStructNow->status = 0;
        myAppStructNow->nextAppStruct = NULL;
        myAppStructNow->lastAppStruct = NULL;
    }
    appManagerCheck();
}

