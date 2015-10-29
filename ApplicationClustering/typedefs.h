#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

//#include "sse_tTypes.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//#define BIT(x) (1 << (x)) // Bitvalue define
//
//// Common values
#ifndef FALSE
	#define FALSE 0
#endif
#ifndef TRUE
	#define TRUE 1
#endif
#ifndef true
	#define true 1
#endif
#ifndef false
	#define false 0
#endif
//
#ifndef NULL
	#define NULL 0
#endif
//
//
//#define FALSE 0
//#define false 0
//#define TRUE  1
//#define true  1
//
///*
//#define BIT0  0x00000001
//#define BIT1  0x00000002
//#define BIT2  0x00000004
//#define BIT3  0x00000008
//#define BIT4  0x00000010
//#define BIT5  0x00000020
//#define BIT6  0x00000040
//#define BIT7  0x00000080
//#define BIT8  0x00000100
//#define BIT9  0x00000200
//*/
//#define BIT10 0x00000400
//#define BIT11 0x00000800
//#define BIT12 0x00001000
//#define BIT13 0x00002000
//#define BIT14 0x00004000
//#define BIT15 0x00008000
//#define BIT16 0x00010000
//#define BIT17 0x00020000
//#define BIT18 0x00040000
//#define BIT19 0x00080000
//#define BIT20 0x00100000
//#define BIT21 0x00200000
//#define BIT22 0x00400000
//#define BIT23 0x00800000
//#define BIT24 0x01000000
//#define BIT25 0x02000000
//#define BIT26 0x04000000
//#define BIT27 0x08000000
//#define BIT28 0x10000000
//#define BIT29 0x20000000
//#define BIT30 0x40000000
//#define BIT31 0x80000000
//
//
////-----------------------------------------------------------------------------
////typedef char            CHAR;    /* 8-bit signed data    */
//typedef unsigned char   BYTE;    /* 8-bit unsigned data  */
//typedef unsigned short  WORD;    /* 16-bit unsigned data */
//typedef long            LONG;    /* 32-bit signed data   */
//typedef unsigned long   ULONG;   /* 32-bit unsigned data */
//typedef unsigned long   DWORD;   /* 32-bit unsigned data */
//
//typedef unsigned char   u08;    /* 8-bit unsigned data  */
//typedef unsigned char   u8_t;    /* 8-bit unsigned data  */
//
//typedef unsigned short  u16;    /* 16-bit unsigned data */
//typedef unsigned short  u16_t;
//
//
// Common data types
//typedef unsigned char		BOOL;

typedef unsigned char		UINT8;
typedef unsigned short		UINT16;
//typedef unsigned long		UINT32;
typedef unsigned long long	UINT64;

typedef signed char		INT8;
typedef signed short		INT16;
//typedef signed long		INT32;
typedef signed long long	INT64;
//
//
///*  typedefs are here  */
//
typedef unsigned char       uint8_t;
typedef unsigned char       uint8;
typedef   signed char        int8_t;
typedef signed char         int8;

typedef unsigned char       uchar;


typedef unsigned short     uint16_t;
typedef   signed short      int16_t;
typedef unsigned short     uint16;

//typedef unsigned long      uint32_t;
//typedef   signed long       int32_t;

//start - previous declaration on linux system
//typedef unsigned long long uint64_t;
//typedef   signed long long  int64_t;
//typedef unsigned long long uint64;
//end - previous declaration on linux system


//
//
//
//typedef enum {False, True}  boolean;
//
//typedef signed char S8; // value range: -128..127
//typedef signed char S08;
//typedef signed char tS08;
//typedef unsigned char U8; // value range: 0..255
//typedef unsigned char U08;
//typedef unsigned char tU08;
//
//
//typedef signed short S16; // value range: -32768..32767
//typedef signed short tS16;
//typedef unsigned short U16; // value range: 0..65535
//typedef unsigned short tU16;
//
//
//typedef signed long S32; // value range: -2147483648..2147483647
//typedef signed long tS32;
//typedef unsigned long U32; // value range: 0..4294967295
//typedef unsigned long tU32;
//
//
//typedef signed long long S64;
//typedef signed long long tS64;
//typedef unsigned long long U64;
//typedef unsigned long long tU64;
//
//typedef S08 *pS8;
//typedef S08 *pS08;
//typedef U08 *pU8;
//typedef U08 *pU08;
//typedef S16 *pS16;
//typedef U16 *pU16;
//typedef S32 *pS32;
//typedef U32 *pU32;
//typedef S64 *pS64;
//typedef U64 *pU64;
//typedef float *pfloat;
//typedef double *pdouble;
//
//typedef unsigned char bool;
/*
typedef U32 BOOL;


typedef BOOL *pBOOL;
*/

#endif
