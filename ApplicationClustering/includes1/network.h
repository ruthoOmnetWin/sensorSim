#ifndef _NETWORK_H_
#define _NETWORK_H_

void networkSendPacket(GENERIC_PACKET* myPacket);
void networkSendPacketDirect(GENERIC_PACKET* myPacket,unsigned short destinationNode);

#endif //_NETWORK_H_
