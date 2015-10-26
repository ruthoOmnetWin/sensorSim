//
// Generated file, do not edit! Created by opp_msgc 4.3 from GenericPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include "ce-application.h"
#include "ce-data.h"
#include <SimpleBattery.h>

/****************************************************************************
 * Applications
 ****************************************************************************/
//#define MYCLASS ClusterApplication::

//Dummy TODO
void MYCLASS applicationLedSwitch(unsigned int led, unsigned int state)
{
    if (led == LED4)
    {
        if (state == ON)
        {
         //   myBaseHost->getDisplayString().setTagArg("b", 3, "red");
            //myBaseHost->getDisplayString().setTagArg("i", 2, "100");
            myBaseHost->getDisplayString().setTagArg("i", 0, "led/red30");

            DrawAmount val(DrawAmount::CURRENT, 10);
                //battery->draw(deviceID, val, account);
            mySimpleBattery->draw(mySimpleBatteryId ,val,0);
            //i=old/proc1,green,100;
        }
        else
        {
            //myBaseHost->getDisplayString().setTagArg("b", 3, "yellow");
            //myBaseHost->getDisplayString().setTagArg("i", 2, "0");
            myBaseHost->getDisplayString().setTagArg("i", 0, "led/gray30");
            DrawAmount val(DrawAmount::CURRENT, 0.5);
                //battery->draw(deviceID, val, account);
            mySimpleBattery->draw(mySimpleBatteryId ,val,0);
        }
    }
}


void MYCLASS ApplicationCheckNeighbours(APP_STRUCT* myAppStruct)
{
    switch (myAppStruct->meta)
    {
        case 00:  // start
            // leds aus
            // Setup ADC12 -
            //  CLK=ACLK, DIV=1, INCH=0000, Ref=ONT
            //  SREF2=0,
            // next event in 10ms

            myAppStruct->start += 10;
            myAppStruct->meta = 10;
            break;
        case 10:
            // Messung ADC0-REF
            myAppStruct->start += 10;
            myAppStruct->meta = 11;
            break;
        case 11:
            // LED 0 ==> ON
            //LedSwitch(LED3, ON);
            myAppStruct->start += 5;
            myAppStruct->meta = 12;
            break;
        case 12:
            // Messung ADC0
            myAppStruct->start += 2;
            myAppStruct->meta = 20;
            //LedSwitch(LED3, ON);
            // LED 0 ==> OFF
            break;
        case 20:

        case 30:
        case 40:

        case 50:
            //Reference disable, Clock = off

        default:  //Remove this app
            myAppStruct->status = APP_STATE_REMOVE;
            globalEvents |= EVENT_APP_MANAGER;
            myAppStruct->meta = 0;
    }
}

/****************************************************************************
 * Execution entry point of any application
 ****************************************************************************/
void MYCLASS applicationExecute(APP_STRUCT* myAppStruct)
{
    //Check application status (Application is invalid or deleted)
    if ((myAppStruct->status != APP_STATE_READY) || (myAppStruct->status != APP_STATE_READY))  //Debug Trap
    {
        globalEvents |= EVENT_APP_MANAGER;
        return;
    }

    //Check dynamic resources (i.e. energy, storage, ...)
    //TODO

    //Execute application(-state)
    switch (myAppStruct->appId)
    {
        case LED1_EIN:
            applicationLedSwitch(LED1, ON);
            if (ticks > myAppStruct->parameterA)
            {
                myAppStruct->status = APP_STATE_REMOVE;
                globalEvents |= EVENT_APP_MANAGER;
            }
            break;
        case LED1_AUS:
            applicationLedSwitch(LED1, OFF);
            if (ticks > myAppStruct->parameterA)
            {
                myAppStruct->status = APP_STATE_REMOVE;
                globalEvents |= EVENT_APP_MANAGER;
            }
            break;
        case LED2_EIN:
            applicationLedSwitch(LED2, ON);
            myAppStruct->meta = 0;
            break;
        case LED2_AUS:
            applicationLedSwitch(LED2, OFF);
            myAppStruct->meta = 0;
            break;
        case LED3_EIN:
            applicationLedSwitch(LED3, ON);
            myAppStruct->meta = 0;
            break;
        case LED3_AUS:
            applicationLedSwitch(LED3, OFF);
            myAppStruct->meta = 0;
            break;
        case LED4_EIN:
            applicationLedSwitch(LED4, ON);
            myAppStruct->meta = 0;
            break;
        case LED4_AUS:
            applicationLedSwitch(LED4, OFF);
            myAppStruct->meta = 0;
            break;
        case META_LED1_FLASH:
            if (myAppStruct->meta == 0)
            {
                applicationLedSwitch(LED1, ON);
                myAppStruct->start += myAppStruct->parameterA;
                myAppStruct->meta = 1;
            }
            else
            {
                applicationLedSwitch(LED1, OFF);
                myAppStruct->start -= myAppStruct->parameterA;
                myAppStruct->meta = 0;
            }
            break;
        case META_LED2_FLASH:
            if (myAppStruct->meta == 0)
            {
                applicationLedSwitch(LED2, ON);
                myAppStruct->start += myAppStruct->parameterA;
                myAppStruct->meta = 1;
            }
            else
            {
                applicationLedSwitch(LED2, OFF);
                myAppStruct->start -= myAppStruct->parameterA;
                myAppStruct->meta = 0;
            }
            break;
        case META_LED3_FLASH:
            if (myAppStruct->meta == 0)
            {
                applicationLedSwitch(LED3, ON);
                myAppStruct->start += myAppStruct->parameterA;
                myAppStruct->meta = 1;
            }
            else
            {
                applicationLedSwitch(LED3, OFF);
                myAppStruct->start -= myAppStruct->parameterA;
                myAppStruct->meta = 0;
            }
            break;
        case META_LED4_FLASH:
            if (myAppStruct->meta == 0)
            {
                applicationLedSwitch(LED4, ON);
                myAppStruct->start += myAppStruct->parameterA;
                myAppStruct->meta = 1;
            }
            else if (myAppStruct->meta == 1)
            {
                applicationLedSwitch(LED4, ON);

                myAppStruct->meta = 1;
                if (myAppStruct->count==1)
                    {
                        applicationLedSwitch(LED4, OFF);
                        myAppStruct->count=0;
                        myAppStruct->meta = 0;
                        myAppStruct->start += myAppStruct->parameterA;
                        //myAppStruct->status = APP_STATE_REMOVE;
                        //globalEvents |= EVENT_APP_MANAGER;
                    }
                else
                {
                    myAppStruct->start += myAppStruct->parameterA;
                    myAppStruct->count--;
                }

            }
            else    //finish
            {
                applicationLedSwitch(LED4, OFF);
            }
            break;
        case META_NEIGHBOURS:
            ApplicationCheckNeighbours(myAppStruct);

            break;
        default:
            break;
    }
    if (myAppStruct->meta == 0 && myAppStruct->count!=0)
        myAppStruct->count--;
}
