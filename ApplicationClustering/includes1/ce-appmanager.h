#ifndef APP_MANAGER_H
#define APP_MANAGER_H

#include "ce-appstructs.h"
#include "ce-applications.h"
#include "hardware.h"
#include "ce-appscheduler.h"
#include "data.h"


void appManagerInit(void);
void appManagerCheck(void);
void appManagerApplicationUpdate(PACKET_APPLICATION_UPDATE* myApplicationPacket);
void appManagerResourceRequest(PACKET_APPLICATION* myApplicationPacket);
void appManagerApplicationRequestFromNet(PACKET_APPLICATION* myApplicationPacket);
void appManagerSendResponse(unsigned int id, unsigned int destination, unsigned int ref,unsigned char response);
void appManagerStartApplicationFromNet(PACKET_APPLICATION* myApplicationPacket);
void appManagerApplicationRequest(PACKET_APPLICATION_REQUEST* myRequestPacket);
#endif

