/*
 * ce-data.h
 *
 *  Created on: 28.08.2013
 *      Author: limir
 */

#ifndef _CE_DATA_H_
#define _CE_DATA_H_

#include "ce-clusterApplication.h"

//RINGBuffers
#define TX_BUFFER_SIZE 512
#define RX_BUFFER_SIZE 256         // TODO - make bigger if possible (2048)
#define TX_UART_BUFFER_SIZE  128
#define RX_UART_BUFFER_SIZE  128

#define LED1    1
#define LED2    2
#define LED3    3
#define LED4    4

#define ON      1
#define OFF     0

#define APP_LISTCOUNT  50

//enum APPLICATIONSTATES
//{
//    APPSTATE_INIT = 0,
//    APPSTATE_APP_RUN,
//    APPSTATE_SLEEP,
//    APPSTATE_UART_RECEIVE,
//    APPSTATE_UART_TRANSMIT,
//    APPSTATE_STANDBY,
//    APPSTATE_RECEIVE,
//    APPSTATE_TRANSMIT,
//    APPSTATE_TRANSMIT_ACK,
//    APPSTATE_KEY_EVENT
//};

//enum NETWORK_STATES
//{
//    NETWORK_STATE_SLEEPING,
//    NETWORK_STATE_ALWAYS_ON,
//    NETWORK_STATE_GO_SLEEPING,
//    NETWORK_STATE_WAKING_UP,
//    NETWORK_STATE_IS_READY
//};


#define WAKEUP_CAUSE_WURX     0x01

/*
#define WAKEUP_CAUSE_RTC      0x02
#define WAKEUP_CAUSE_LPC      0x04
#define WAKEUP_CAUSE_INT0     0x08



#define WAKEUP_CAUSE_CONFIG   0x40
#define WAKEUP_CAUSE_EXPLORE  0x80
*/
#define WAKEUP_CAUSE_APP_RUN   0x10
#define WAKEUP_CAUSE_RX        0x20
#define WAKEUP_CAUSE_BUTTON_1  0x01
#define WAKEUP_CAUSE_BUTTON_2  0x02


#define DATA_TRANSFER_STARTING   0x01
#define DATA_TRANSFER_RUNNING    0x02
#define DATA_TRANSFER_DEBUG_1    0x04
#define DATA_TRANSFER_DEBUG_2    0x08

#define MODUS_MEASUREMENT   0x01
#define MODUS_WAKEUP        0x02
#define MODUS_EXPLORATION   0x04
#define MODUS_CONFIGURATION 0x08
#define MODUS_TRANSMISSION  0x10
#define MODUS_COM           0x20
#define MODUS_ALERT         0x40
#define MODUS_SLEEP         0x80


#endif
