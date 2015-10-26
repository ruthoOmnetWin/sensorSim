#ifndef _SPI_H_
#define _SPI_H_


#include "msp430x16x.h"
#include "hardware.h"

void spiInit(void);
void SPI_SelectDevice(unsigned char device);
void  SPI_UnselectDevice(void);
void spiDummyByte(unsigned char data);
unsigned char spiTransferByte(unsigned char data);
unsigned long spiTransfer32(unsigned long data);
unsigned short spiTransfer16(unsigned short data);
unsigned short  SPIWrite(unsigned char * ptrBuffer, unsigned short  ui_Len);
unsigned short SPIRead(unsigned char * ptrBuffer, unsigned short ui_Len);


#endif

