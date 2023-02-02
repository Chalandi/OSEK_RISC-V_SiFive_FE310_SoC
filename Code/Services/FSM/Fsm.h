// ****************************************************************************************************
// Filename    : Fsm.h
// 
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 27.06.2018
// 
// Description : Finite State Machine (FSM) Framework - Header file
//
// Licence     : GNU General Public License v3.0
//
// ****************************************************************************************************

#ifndef _FSM_H_
#define _FSM_H_


typedef enum {

    FSM_RET_OK,
    FSM_RET_NOK

} fsm_ret_t;

typedef unsigned short  fsm_event_t;
typedef unsigned char   fsm_state_t;
typedef fsm_ret_t (*fsm_action_t)(void);


typedef struct{
    const fsm_event_t   event;
    const fsm_state_t   TargetState;
          fsm_action_t  action;
} fsm_trans_t;

typedef struct{
    fsm_state_t    parent;
    fsm_state_t    child;
    fsm_state_t    histIdx;
    unsigned int   sizeTransTab;
    const fsm_trans_t*   trans_tab;
    fsm_action_t   entryFunc;
    fsm_action_t   exitFunc;
} fsm_graph_t;


typedef struct {
    const fsm_graph_t*  pGraph;
    const fsm_state_t   nbStates;
    const fsm_state_t   initState;
          fsm_state_t   oldState;
          fsm_state_t   currentState;
          fsm_state_t*  pHistory;
} fsm_t;


#define NO_FSM_STATE   (fsm_state_t)0xFF
#define NO_FSM_TARGET  (fsm_state_t)0xFF
#define NO_FSM_ACTION  FsmVoidFunc
#define NO_FSM_PARENT  (fsm_state_t)0xFF
#define NO_FSM_CHILD   (fsm_state_t)0xFF
#define NO_FSM_HISTORY (fsm_state_t)0xFF
#define DUMMY_EVENT    (NB_OF_EVENTS + 1)


void Fsm_Create(fsm_t* pFsm, fsm_state_t* pHistory);
void Fsm_Delete(fsm_t * pFsm);
fsm_state_t Fsm_GetCurrentState(fsm_t * pFsm);
fsm_state_t Fsm_GetParentState(fsm_t * pFsm);
fsm_ret_t Fsm_Stimulate(fsm_t * pFsm, fsm_event_t event);

#endif
