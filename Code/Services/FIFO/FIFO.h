#ifndef _FIFO_H_
#define _FIFO_H_

/***************************************************************************************************
**                  Type Definitions                                                              **
***************************************************************************************************/
typedef struct {
unsigned int        PopPtr;
unsigned int        PushPtr;
const unsigned int  size;
unsigned char*      buf;
}tfifoData;

/***************************************************************************************************
**                  Macros                                                                        **
***************************************************************************************************/
#define CIRCULAR_FIFO_DEF(id,fifosize)         \
unsigned char buffer_##id[fifosize]={0};     \
tfifoData Fifo_##id = {0,0,fifosize,buffer_##id}


#define pCIRCULAR_FIFO(id) (tfifoData*)&Fifo_##id

/***************************************************************************************************
**                  Functions Prototypes                                                          **
***************************************************************************************************/
unsigned char CircularFIFO_IsEmpty(tfifoData* pfifo);
unsigned char CircularFIFO_IsFull(tfifoData* pfifo);
unsigned int  CircularFIFO_GetAvailableSize(tfifoData* pfifo);
unsigned int  CircularFIFO_GetCurrentConsumption(tfifoData* pfifo);
unsigned char CircularFIFO_Push(tfifoData* pfifo, unsigned char* data, unsigned int size);
unsigned char CircularFIFO_Pop(tfifoData* pfifo, unsigned char* data, unsigned int size);
unsigned char CircularFIFO_ReadCopy(tfifoData* pfifo, unsigned char* data, unsigned int size);




#endif
