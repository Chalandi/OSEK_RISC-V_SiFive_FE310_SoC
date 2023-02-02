// *****************************************************************************************************************
// Filename      : IPC.h
//
// Author        : Chalandi Amine
//               
// Owner         : Chalandi Amine
//               
// Date          : 01.10.2018
//               
// Description   : Inter-process communication services
// 
// *****************************************************************************************************************

#ifndef __IPC_H__
#define __IPC_H__


/***************************************************************************************************
**                  Includes                                                                      **
***************************************************************************************************/
#include"OsTcb.h"
#include"Platform_Types.h"
#include"fifo.h"


/***************************************************************************************************
**                  Types definition                                                              **
***************************************************************************************************/

typedef struct{
  uint16 const owner;       //Osek target Task id
  uint16 const res;         //Osek ressource
  uint16 const evt;         //Osek event
  tfifoData* const pQueue;  //Queue pointer
}IpcMbxCfg;


typedef struct{
  uint16 id;    //Message Id
  uint16 size;  //size of data
  uint8* data;  //pointer to the data
}IpcMbxdata;

typedef enum{
  IPC_NOK = 0,
  IPC_OK
}IpcStatus;


/***************************************************************************************************
**                  Macros                                                                        **
***************************************************************************************************/
#define IPC_DEF_MBX_QUEUE(TaskId, size, ressource, event)  CIRCULAR_FIFO_DEF(TaskId,size); \
const IpcMbxCfg IpcMbx_##TaskId = {.owner=TaskId, .res=ressource, .evt=event, .pQueue=&Fifo_##TaskId}

#define pIPC(Owner) &IpcMbx_##Owner
#define gIPC(Owner) IpcMbx_##Owner

/***************************************************************************************************
**                  Prototypes                                                                    **
***************************************************************************************************/
IpcStatus Ipc_SendQueuedData(IpcMbxCfg const * const  MsgBox, IpcMbxdata const* Msgdata);
IpcStatus Ipc_ReceiveQueuedData(IpcMbxCfg const * const  MsgBox, IpcMbxdata const* Msgdata);

#endif // __OSEK_COM_H__
