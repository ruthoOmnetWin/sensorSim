#ifndef _CIRC_BUFFER_H_
#define _CIRC_BUFFER_H_

#ifndef CHAR_ESC
  #define CHAR_ESC	0xFD
#endif 

#ifndef CHAR_START
  #define CHAR_START	0xFE
#endif 

#ifndef CHAR_END
  #define CHAR_END	0xFF
#endif 

#ifndef CHAR_SPECIAL_BLOCK
  #define SPECIAL_BLOCK	0xFB  //Special Block
#endif 



typedef struct 
{
	//unsigned char id;
	unsigned int count;
	unsigned int posRead;
	unsigned int posWrite;
	unsigned char statusFull;
	unsigned char statusEmpty;
	unsigned int size;
	unsigned char *buffer;
	unsigned char signal;
} queue;




void queueInit(queue* q, unsigned char* buffer,unsigned int size );
void queueInsert (queue* q, unsigned char myChar);
void queueInsertEscaped (queue* q, unsigned char myChar);
int  queueRemove(queue* q, unsigned char* myChar);
int  queueRemoveEscaped(queue* q, unsigned char* myChar);
int queueInsertObjectEscaped(queue *q,void* obj,unsigned char size);
int queueInsertObject(queue *q,void* obj,unsigned char size);
int queueRemoveBlock(queue *q, unsigned char* myArray, unsigned int maxsize);
int queueInsertObjectSpecial(queue *q,void* obj,unsigned char size);
int queueRemoveObjectSpecial(queue *q,void* obj,unsigned char maxsize);
int queueRemoveEscapedTmp(queue *q, unsigned char* myChar,unsigned int* posReadTmp);
int queueClear(queue *q);
#endif
