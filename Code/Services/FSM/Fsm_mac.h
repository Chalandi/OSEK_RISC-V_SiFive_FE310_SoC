// ****************************************************************************************************
// Filename    : Fsm_mac.h
// 
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 27.06.2018
// 
// Description : Finite State Machine (FSM) Framework - x macro generation
//
// Licence     : GNU General Public License v3.0
//
// ****************************************************************************************************

#ifndef _FSM_MAC_H_
#define _FSM_MAC_H_


#endif

#include"Fsm.h"


#ifdef GRAPH
#undef GRAPH
#endif

#ifdef STATE
#undef STATE
#endif

#ifdef GRAPH_END
#undef GRAPH_END
#endif

#ifdef STATE_DEF
#undef STATE_DEF
#endif

#ifdef TRANS
#undef TRANS
#endif

#ifdef STATE_END
#undef STATE_END
#endif

#ifdef FSM
#undef FSM
#endif

#ifdef EVENT_DEF
#undef EVENT_DEF
#endif

#ifdef EVENT
#undef EVENT
#endif

#ifdef EVENT_END
#undef EVENT_END
#endif

#ifdef FSM_PTR
#undef FSM_PTR
#endif

#ifdef HIST
#undef HIST
#endif

#if defined(FSM_GEN_PROTO)

#define GRAPH(FSM_NAME)
#define STATE(STATE_NAME, PARENT_STATE_NAME, STATE_ENTRY_ACTION, STATE_EXIT_ACTION, CHILD_STATE, HISTORY_INDEX) extern fsm_ret_t STATE_ENTRY_ACTION##(void); extern fsm_ret_t STATE_EXIT_ACTION##(void);
#define GRAPH_END

#define STATE_DEF(STATE_NAME)
#define TRANS(EVENT_NAME, TARGET_NAME, ACTION) extern fsm_ret_t ACTION##(void);
#define STATE_END

#define FSM(FSM_NAME, INIT_STATE)

#define EVENT_DEF
#define EVENT(x)
#define EVENT_END

#define FSM_PTR(NAME)

#define HIST(NAME,SIZE)

#elif defined(FSM_GEN_ENUM)

#define GRAPH(FSM_NAME) enum { 
#define STATE(STATE_NAME, PARENT_STATE_NAME, STATE_ENTRY_ACTION, STATE_EXIT_ACTION, CHILD_STATE, HISTORY_INDEX) STATE_NAME##,
#define GRAPH_END NB_OF_STATES};

#define STATE_DEF(STATE_NAME)
#define TRANS(EVENT_NAME, TARGET_NAME, ACTION)
#define STATE_END

#define FSM(FSM_NAME, INIT_STATE)

#define EVENT_DEF enum{
#define EVENT(x) x##,
#define EVENT_END   NB_OF_EVENTS};

#define FSM_PTR(NAME)

#define HIST(NAME,SIZE)

#elif defined(FSM_GEN_GRAPH)

#define GRAPH(FSM_NAME) const fsm_graph_t Fsm_##FSM_NAME##_Graph[] = {
#define STATE(STATE_NAME, PARENT_STATE_NAME, STATE_ENTRY_ACTION, STATE_EXIT_ACTION, CHILD_STATE, HISTORY_INDEX) {PARENT_STATE_NAME, CHILD_STATE, (fsm_state_t)HISTORY_INDEX, (sizeof(Fsm_##STATE_NAME##_Trans)/sizeof(fsm_trans_t)), &Fsm_##STATE_NAME##_Trans[0], STATE_ENTRY_ACTION, STATE_EXIT_ACTION},
#define GRAPH_END };

#define STATE_DEF(STATE_NAME) const fsm_trans_t Fsm_##STATE_NAME##_Trans[] = {
#define TRANS(EVENT_NAME, TARGET_NAME, ACTION) {EVENT_NAME, TARGET_NAME, ACTION},
#define STATE_END    };

#define FSM(FSM_NAME, INIT_STATE)  fsm_t Fsm_##FSM_NAME = {&Fsm_##FSM_NAME##_Graph[0], (sizeof(Fsm_##FSM_NAME##_Graph)/sizeof(fsm_graph_t)), INIT_STATE, NO_FSM_STATE, NO_FSM_STATE, (fsm_state_t*)0}; 

#define EVENT_DEF
#define EVENT(x)
#define EVENT_END

#define FSM_PTR(NAME) (fsm_t*)(&Fsm_##NAME)

#define HIST(NAME,SIZE) fsm_state_t FsmHist_##NAME##[SIZE+1];

#else

#define GRAPH(FSM_NAME)
#define STATE(STATE_NAME, PARENT_STATE_NAME, STATE_ENTRY_ACTION, STATE_EXIT_ACTION, CHILD_STATE, HISTORY_INDEX)
#define GRAPH_END

#define STATE_DEF(STATE_NAME)
#define TRANS(EVENT_NAME, TARGET_NAME, ACTION)
#define STATE_END

#define FSM(FSM_NAME, INIT_STATE) extern fsm_t Fsm_##FSM_NAME;

#define EVENT_DEF
#define EVENT(x)
#define EVENT_END

#define FSM_PTR(NAME)

#define HIST(NAME,SIZE) extern fsm_state_t FsmHist_##NAME##[SIZE];

#endif


#ifdef FSM_GEN_PROTO
#undef FSM_GEN_PROTO
#endif

#ifdef FSM_GEN_ENUM
#undef FSM_GEN_ENUM
#endif

#ifdef FSM_GEN_GRAPH
#undef FSM_GEN_GRAPH
#endif



