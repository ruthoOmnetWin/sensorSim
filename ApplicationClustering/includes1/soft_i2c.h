#ifndef _SOFT_I2C_H_
#define _SOFT_I2C_H_

#define SOFT_I2C

#include "msp430x16x.h"
#include "hardware.h"

#define SDA    0x02   //P3.1
#define SCL    0x08   //P3.3

#define SDA_IN  (P3DIR &= ~SDA)
#define SDA_OUT  (P3DIR |= SDA)

#define SCL_IN  (P3DIR &= ~SCL) 
#define SCL_OUT (P3DIR |=  SCL) 

#define SDA_DATA (P3IN & SDA)

#define SDA_LOW   (P3DIR |= SDA)
#define SDA_HIGH  (P3DIR &= ~SDA)
#define SCL_LOW   (P3DIR |=  SCL)
#define SCL_HIGH  (P3DIR &= ~SCL)




void wait(unsigned char cycles);
void MSP430_SWI2C_init(void);
void MSP430_SWI2C_start(void);
void MSP430_SWI2C_stop(void);
unsigned char MSP430_SWI2C_ack(void);
void MSP430_SWI2C_nack(void);
unsigned char MSP430_SWI2C_txByte(unsigned char data);
unsigned char MSP430_SWI2C_rxByte(unsigned char ack);
void MSP430_SWI2CMST_writeBlock(unsigned char* data, unsigned char cnt);
void MSP430_SWI2CMST_readBlock(unsigned char* data, unsigned char cnt);

#endif
