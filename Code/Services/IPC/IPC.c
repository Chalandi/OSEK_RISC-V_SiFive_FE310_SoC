// *****************************************************************************************************************
// Filename      : IPC.c
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

#include"IPC.h"
#include"OsAPIs.h"


IpcStatus Ipc_SendQueuedData(IpcMbxCfg const * const MsgBox, IpcMbxdata const* Msgdata)
{

  const uint16 size = sizeof(Msgdata->id) + sizeof(Msgdata->size) + Msgdata->size;
  OsTaskStateType taskstate;

  /* get the owner state status */
  (void)OS_GetTaskState(MsgBox->owner, &taskstate);

  /* before sending the data check if the queue has enough space or not 
     and the target task not suspended */
  if(size <= CircularFIFO_GetAvailableSize(MsgBox->pQueue) && (taskstate != SUSPENDED))
  {
    /* lock the mailbox */
    OS_GetResource(MsgBox->res);

    /* push data into the queue */
    (void)CircularFIFO_Push(MsgBox->pQueue, (uint8*)&Msgdata->id, sizeof(Msgdata->id));
    (void)CircularFIFO_Push(MsgBox->pQueue, (uint8*)&Msgdata->size, sizeof(Msgdata->size));
    (void)CircularFIFO_Push(MsgBox->pQueue, (uint8*)Msgdata->data, Msgdata->size);

    /* unlock the mailbox */
    OS_ReleaseResource(MsgBox->res);

    /* set event */
    OS_SetEvent(MsgBox->owner,MsgBox->evt);

    return(IPC_OK);
  }
  else
  {
    return(IPC_NOK);
  }
}

IpcStatus Ipc_ReceiveQueuedData(IpcMbxCfg const * const  MsgBox, IpcMbxdata const* Msgdata)
{
  /* check if the queue is not empty */
  if(!CircularFIFO_IsEmpty(MsgBox->pQueue))
  {
    /* lock the mailbox */
    OS_GetResource(MsgBox->res);

    /* push data into the queue */
    (void)CircularFIFO_Pop(MsgBox->pQueue, (uint8*)&Msgdata->id, sizeof(Msgdata->id));
    (void)CircularFIFO_Pop(MsgBox->pQueue, (uint8*)&Msgdata->size, sizeof(Msgdata->size));
    (void)CircularFIFO_Pop(MsgBox->pQueue, (uint8*)Msgdata->data, Msgdata->size);

    /* unlock the mailbox */
    OS_ReleaseResource(MsgBox->res);

    return(IPC_OK);
  }
  else
  {
    return(IPC_NOK);
  }
}
