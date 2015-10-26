/*
 * ce-data.cpp
 *
 *  Created on: 28.08.2013
 *      Author: limir
 */

#include "ce-clusterApplication.h"
#include <SimpleBattery.h>
#include <PhyLayerBattery.h>

ClusterApplication::ClusterApplication(BaseModule* baseModule, int oGate)
{
    //this->myData = new Data();
    this->myOutGate = oGate;
    this->myBaseModule = baseModule;

    sysTimer = new cMessage("clusterApplicationSysTimer");
    sysTimer->addPar("timerId");
    sysTimer->addPar("timerValue");
    sysTimer->addPar("timerSrc");

    sleepTimer = new cMessage("clusterApplicationSleepTimer");
    clusterApplicationEvents = 0;

    //clear all timers
    for (int i = 0; i < TIMER_ID_MAX; i++)
    {
        timers[i] = 0;
    }
    mySimpleBattery = new SimpleBattery();
    myPhyLayerBattery = new PhyLayerBattery();
    sleepTimeout = SLEEP_TIMEOUT;

    clusterApplicationUpdateTickCounter(0); //Clear Systick
    resourceManagerInit();
    appschedulerInit();
    appManagerInit();
    coordinatorInit();

    appManagerCheck();
    wakeupSleepInit();
}

ClusterApplication::~ClusterApplication()
{

}

void ClusterApplication::clusterApplicationCancelTimers(void)
{
    if (sysTimer->isScheduled())
        myBaseModule->cancelEvent(sysTimer);
    if (sleepTimer->isScheduled())
        myBaseModule->cancelEvent(sleepTimer);
}

void ClusterApplication::clusterApplicationTimerEvent(unsigned int timerId, unsigned long timerValue)
{
    //cancel timer
    //TODO repeating timers ?
    timers[timerId] = 0;
    switch (timerId)
    {
        case TIMER_ID_COORDINATOR_REQUEST_TIMEOUT:
            //coordinatorManager();
            coordinatorManagerProcessRequest();
            break;
        case TIMER_ID_COORDINATOR_UPDATE_TIMEOUT:
            coordinatorManager();
            break;
        case TIMER_ID_APPLICATION_SCHEDULER:
            applicationExecute(appFirstEntry);
            appschedulerCalcNextExecution(appFirstEntry);
            appschedulerUpdateFirstApp();
            //APP_RUN
            break;
            //case TIMER_ID_WAKEUP_SLEEP_TIMER:
            //wakeupSleepEnterSleep();
            //Sleep/Wakeup
            //  break;
        default:
            break;
    }

    if (globalEvents & EVENT_APP_MANAGER)
    {
        globalEvents &= ~EVENT_APP_MANAGER;
        appManagerCheck();
    }
    //set next timer
    clusterApplicationRefreshTimerEvent();
}

void ClusterApplication::clusterApplicationRefreshTimerEvent(void)
{
    unsigned long nextTimerValue = -1; //use maximum value
    unsigned char nextTimerId = 0;

    for (int i = 0; i < TIMER_ID_MAX; i++)
    {
        //Timer is ready for interrupt
//        if ((timer[i]>0) && (lastTimerEvent>timer[i]) && (ticks>timer[i]))
//        {
//
//        }

        //find the next timer
        if ((timers[i] > ticks) && (timers[i] < nextTimerValue))
        {
            nextTimerValue = timers[i];
            nextTimerId = i;
        }

    }
    if (nextTimerId == 0)
        return;

    //TODO bad casting
    unsigned int tmpUInt = sysTimer->par("timerId");
    unsigned long tmpULong = sysTimer->par("timerValue");
    if ((tmpUInt == nextTimerId) && (tmpULong == nextTimerValue))
    {
        return;
    }

    sysTimer->par("timerId") = nextTimerId;
    sysTimer->par("timerValue") = nextTimerValue;

    //calculate event and schedule timer
    if (sysTimer->isScheduled())
    {
        myBaseModule->cancelEvent(sysTimer);
    }
    myBaseModule->scheduleAt(simTime() + ((nextTimerValue - ticks) * 0.001) + uniform(0, 0.001), sysTimer);

    lastTimerEvent = ticks;
}

// set a spezificated timer
void ClusterApplication::clusterApplicationUpdateTickCounter(unsigned long value)
{
    ticks = value;
}

void ClusterApplication::clusterApplicationUpdateTimer(unsigned char timerId, unsigned char type, unsigned int value)
{
    if (timerId >= TIMER_ID_MAX)
        return;   //error

    //unsigned long ticks = delay;

    switch (type)
    {
        case TIMER_TYPE_ADD:
            timers[timerId] += value;
            break;
        case TIMER_TYPE_DELETE:
            timers[timerId] = 0;
            break;
        case TIMER_TYPE_OFFSET:
            timers[timerId] = ticks + value;
            break;
        case TIMER_TYPE_SET:
            timers[timerId] = value;
            break;

    }
    clusterApplicationRefreshTimerEvent();
}
