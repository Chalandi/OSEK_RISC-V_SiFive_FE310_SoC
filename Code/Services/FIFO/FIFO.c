// *****************************************************************************
// Filename    : FIFO.c
// 
// Author      : Chalandi Amine
// Owner       : Chalandi Amine
// 
// Date        : 14.08.2017
// 
// Description : Circulair FIFO Library.
// 
// *****************************************************************************

#include "fifo.h"


//------------------------------------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  
///
/// \return 
//------------------------------------------------------------------------------------------------------------------
unsigned char CircularFIFO_IsEmpty(tfifoData* pfifo)
{
  return((pfifo->PopPtr == pfifo->PushPtr) ? 1 : 0);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  
///
/// \return 
//------------------------------------------------------------------------------------------------------------------
unsigned char CircularFIFO_IsFull(tfifoData* pfifo)
{
  unsigned char result=0;

  if((pfifo->PopPtr == 0 && (pfifo->PushPtr + 1) == pfifo->size) || (pfifo->PopPtr == (pfifo->PushPtr +1)))
  {
    result = 1;
  }
  return(result);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  
///
/// \return 
//------------------------------------------------------------------------------------------------------------------
unsigned int CircularFIFO_GetAvailableSize(tfifoData* pfifo)
{
  if(pfifo->PopPtr < pfifo->PushPtr)
  {
    return((unsigned int)(pfifo->size - pfifo->PushPtr + pfifo->PopPtr));
  }
  else if(pfifo->PopPtr > pfifo->PushPtr)
  {
    return((unsigned int)(pfifo->PopPtr - pfifo->PushPtr));
  }
  else
  {
    return((unsigned int)(pfifo->size));
  }
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  
///
/// \return 
//------------------------------------------------------------------------------------------------------------------
unsigned int CircularFIFO_GetCurrentConsumption(tfifoData* pfifo)
{
  return((unsigned int)(pfifo->size - CircularFIFO_GetAvailableSize(pfifo)));
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  
///
/// \return 
//------------------------------------------------------------------------------------------------------------------
unsigned char CircularFIFO_Push(tfifoData* pfifo, unsigned char* data, unsigned int size)
{
  if(size <= CircularFIFO_GetAvailableSize(pfifo))
  {
    for(int cpt=0;cpt < size; cpt++)
    {
      if(pfifo->PushPtr == pfifo->size)
      {
        pfifo->PushPtr = 0;
      }
      pfifo->buf[pfifo->PushPtr] = data[cpt];
      pfifo->PushPtr++;
    }
    return(1);
  }
  else
  {
    /* No more space in FIFO */
    return(0);
  }
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  
///
/// \return 
//------------------------------------------------------------------------------------------------------------------
unsigned char CircularFIFO_Pop(tfifoData* pfifo, unsigned char* data, unsigned int size)
{
  if(size <= CircularFIFO_GetCurrentConsumption(pfifo))
  {
    /* Available data */
    for(int cpt=0;cpt < size; cpt++)
    {
      if(pfifo->PopPtr == pfifo->size)
      {
        pfifo->PopPtr = 0;
      }
      data[cpt] = pfifo->buf[pfifo->PopPtr];
      pfifo->PopPtr++;
    }
    return(1);
  }
  else
  {
    /* Not available data size */
    return(0);
  }
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  
///
/// \return 
//------------------------------------------------------------------------------------------------------------------
unsigned char CircularFIFO_ReadCopy(tfifoData* pfifo, unsigned char* data, unsigned int size)
{
  if(size <= CircularFIFO_GetCurrentConsumption(pfifo))
  {
    /* Available data */
    unsigned int ptr = pfifo->PopPtr;
    for(int cpt=0;cpt < size; cpt++)
    {
      if(ptr == pfifo->size)
      {
        ptr = 0;
      }
      data[cpt] = pfifo->buf[ptr];
      ptr++;
    }
    return(1);
  }
  else
  {
    /* Not available data size */
    return(0);
  }
}
