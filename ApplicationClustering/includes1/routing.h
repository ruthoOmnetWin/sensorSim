/****************************************************************************
 *  Nannet / PLANet                                                         *
 ****************************************************************************
 *  File: routing.h                                                         *
 ****************************************************************************
 *  Versions                                                                *
 *  1.00   (2012-16-04)                                                     *
 ****************************************************************************/


#ifndef ROUTING_H
#define ROUTING_H

#include "packets.h"
#include "config.h"
#include "data.h"

// Maimale Anzahl möglicher Einträge 
// benötige Bytes = Anzahl * 4

#define ENTRIES 2

//Leerer Eintrag --> destinationId == 0xFFFF && hopId != 0xFFFF
//Tabellenende   --> destinationId == hopId == 0xFFFF

typedef struct ROUTING_ENTRY
{
  unsigned short destinationId;
  unsigned short hopId;
} routingEntry;

extern routingEntry routingTable [ENTRIES];


void routingAddEntry(unsigned short destinationId, unsigned short hopId);

void routingDelEntry(unsigned short destinationId);

unsigned short routingGetEntry(unsigned short destinationId);
void routingForwardingPacket(ROUTING_INFO *myPacket);
void routingForwardingRoutingPacket(ROUTING_INFO *myPacket,unsigned short destinationNode);
void routingProcessRoutingPacket(ROUTING_INFO *myPacket);
void routingInit(void);
unsigned short routingGetChildreen(unsigned short id);

#endif
