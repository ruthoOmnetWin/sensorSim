#ifndef _DS1339_H_
#define _DS1339_H_

typedef struct TIME_STRUCT_
{
    unsigned char seconds;
    unsigned char minutes;
    unsigned char hours;
    unsigned char options;
} TIME;

typedef struct DATE_STRUCT_
{
    unsigned char dayOfWeek;
    unsigned char day;
    unsigned char month;
    unsigned char year;
} DATE;


#define DS1339_REG_ALARM1_S 0x07
#define DS1339_REG_ALARM1_M 0x08
#define DS1339_REG_ALARM1_H 0x09
#define DS1339_REG_ALARM1_D 0x0A

#define DS1339_REG_ALARM2_M 0x0B
#define DS1339_REG_ALARM2_H 0x0C
#define DS1339_REG_ALARM2_D 0x0D

#define DS1339_REG_CONTROL  0x0E
#define DS1339_REG_STATUS   0x0E


#define DS1339_A1IE         0x01
#define DS1339_A2IE         0x02
#define DS1339_INTCN        0x04


unsigned short DS1339GetTime(TIME* myTimeStruct);
unsigned short DS1339GetDate(DATE* myDateStruct);
void DS1339ResetIRQ(void);
void InitDs1339(void);
#endif

