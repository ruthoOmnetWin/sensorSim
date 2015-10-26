#ifndef _ATFLASH_H
#define _ATFLASH_H

#include "msp430x16x.h"
#include "hardware.h"
#include "typedefs.h"
#include "spi.h"

#define MEMORY_COMMAND_READ_LOW_SPEED             0x03
#define MEMORY_COMMAND_READ_HIGH_SPEED            0x0B
#define MEMORY_COMMAND_WRITE_ENABLE               0x06
#define MEMORY_COMMAND_WRITE_DISABLE              0x04
#define MEMORY_COMMAND_ERASE_BLOCK_4KB            0x20
#define MEMORY_COMMAND_ERASE_BLOCK_16KB           0x52
#define MEMORY_COMMAND_ERASE_BLOCK_32KB           0xD8
#define MEMORY_COMMAND_ERASE_CHIP                 0x60
#define MEMORY_COMMAND_PROGRAMM_BYTE              0x02
#define MEMORY_COMMAND_PROGRAMM_AUTO_INCREMENT    0xAD


#define MEMORY_COMMAND_READ_JEDEC_ID              0x9F
#define MEMORY_COMMAND_WRITE_STATUS_REGISTER      0x01
#define MEMORY_COMMAND_READ_STATUS_REGISTER       0x05
#define MEMORY_COMMAND_ENABLE_WRITE_STATUS_REG    0x50



void memoryWriteData(unsigned long address, unsigned char data);
unsigned char memoryReadData(unsigned long address);

void memoryReadDataBlock(unsigned long address, unsigned char* datapointer, unsigned int size);
void memoryWriteDataBlock(unsigned long address, unsigned char* datapointer, unsigned int size);
void memoryWriteDisable(void);
bool memoryWriteEnable(void);
void memoryEraseBlock(unsigned long address);



//
//void memoryWriteData1(unsigned char add1, unsigned char add2, unsigned  char add3, unsigned char data);
//unsigned char memoryReadData1(unsigned char add1, unsigned char add2,  unsigned char add3);

#endif
