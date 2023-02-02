// ****************************************************************************************************
// Filename    : Fsm.c
// 
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 27.06.2018
// 
// Description : Finite State Machine (FSM) Framework - APIs
//
// Licence     : GNU General Public License v3.0
//
// ****************************************************************************************************

#include"Fsm.h"


//----------------------------------------------------------------------------------
/// \brief  This function create the FSM instance and execute the default state.
///
/// \param  fsm_t* pFsm : pointer to Fsm graph data struct
///         fsm_state_t* pHistory: pointer to the history array
///
/// \return void
//----------------------------------------------------------------------------------
void Fsm_Create(fsm_t* pFsm, fsm_state_t* pHistory)
{
  fsm_state_t parent = NO_FSM_STATE;

  pFsm->currentState = pFsm->initState;

  pFsm->pHistory = pHistory;

  /* run the entry point of the init state */
  if(pFsm->pGraph[pFsm->currentState].entryFunc != (fsm_action_t)(0))
  {
    pFsm->pGraph[pFsm->currentState].entryFunc();
  }

  /* search for all child states */
  while(pFsm->pGraph[pFsm->currentState].child != NO_FSM_CHILD)
  {

    /* set the child state as the current state */
    pFsm->currentState = pFsm->pGraph[pFsm->currentState].child;

    /* check if the parent of the current state has a history */
    parent = pFsm->pGraph[pFsm->currentState].parent;

    if(parent != NO_FSM_STATE && pFsm->pGraph[parent].histIdx != NO_FSM_HISTORY)
    {
      pFsm->pHistory[pFsm->pGraph[parent].histIdx] = pFsm->currentState;
    }

    /* run the entry function of the child state */
    if(pFsm->pGraph[pFsm->currentState].entryFunc != (fsm_action_t)(0))
    {
    pFsm->pGraph[pFsm->currentState].entryFunc();
    }
  }

}

//-----------------------------------------------------------------------------
/// \brief  This function is called every time the internal event 
///         NO_FSM_ACTION is set.
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------
void FsmVoidFunc(void)
{
}

//-----------------------------------------------------------------------------
/// \brief  This function deinit the FSM engine for the graph 
///         pointed by pFsm.
///
/// \param  fsm_t* pFsm : pointer to Fsm graph data struct
///
/// \return void
//-----------------------------------------------------------------------------
void Fsm_Delete(fsm_t * pFsm)
{
  pFsm->currentState = 0;
  pFsm->pGraph = 0;
  pFsm->pHistory = 0;
}

//-----------------------------------------------------------------------------
/// \brief  This function return the current state of the graph
///
/// \param  fsm_t* pFsm : pointer to Fsm graph data struct
///
/// \return fsm_state_t
//-----------------------------------------------------------------------------
fsm_state_t Fsm_GetCurrentState(fsm_t * pFsm)
{
  return(pFsm->currentState);
}

//-----------------------------------------------------------------------------
/// \brief  This function return the parent state of the current state 
///
/// \param  fsm_t* pFsm : pointer to Fsm graph data struct
///
/// \return fsm_state_t
//-----------------------------------------------------------------------------
fsm_state_t Fsm_GetParentState(fsm_t * pFsm)
{
  fsm_state_t currentState = pFsm->currentState;
  return(pFsm->pGraph[currentState].parent);
}

//-----------------------------------------------------------------------------
/// \brief  This function stimulate the FSM graph
///
/// \param  fsm_t* pFsm : pointer to Fsm graph data struct
///         fsm_event_t event 
///
/// \return fsm_state_t
//-----------------------------------------------------------------------------
fsm_ret_t Fsm_Stimulate(fsm_t * pFsm, fsm_event_t event)
{
  fsm_state_t state = pFsm->currentState;
  fsm_ret_t ActionIsFound = FSM_RET_NOK;
  fsm_state_t ChildState = NO_FSM_STATE;
  fsm_state_t parent = NO_FSM_STATE;
  fsm_action_t pTransitionAction = (void*)0;

  for(;;)
  {
    /* search the event in the transition table of the current task */
    for(unsigned int EvtIdx=0; (EvtIdx < pFsm->pGraph[state].sizeTransTab); EvtIdx++)
    {
      if(pFsm->pGraph[state].trans_tab[EvtIdx].event == event && pFsm->pGraph[state].trans_tab[EvtIdx].action != (const fsm_action_t)NO_FSM_ACTION)
      {
        /* save the action pointer */
        pTransitionAction = pFsm->pGraph[state].trans_tab[EvtIdx].action;

        ActionIsFound = FSM_RET_OK;
      }

      /* check if the transition has a target state */
      if(pFsm->pGraph[state].trans_tab[EvtIdx].event == event && pFsm->pGraph[state].trans_tab[EvtIdx].TargetState != NO_FSM_TARGET)
      {

         /* run the exit function of the child state (if the child exist) */
         if(ChildState != NO_FSM_STATE && pFsm->pGraph[ChildState].exitFunc != (fsm_action_t)(0))
         {
          pFsm->pGraph[ChildState].exitFunc();
         }

         /* run the exit function of the current state */
         if(pFsm->pGraph[state].exitFunc != (fsm_action_t)(0))
         {
          pFsm->pGraph[state].exitFunc();
         }

         /* execute the transition action */
         if(ActionIsFound == FSM_RET_OK)
         {
           pTransitionAction();
         }

        /* Change the current state to the target state */
        pFsm->currentState = pFsm->pGraph[state].trans_tab[EvtIdx].TargetState;

        /* check if the parent of the current state has a history */
        parent = pFsm->pGraph[pFsm->currentState].parent;

        if(parent != NO_FSM_STATE && pFsm->pGraph[parent].histIdx != NO_FSM_HISTORY)
        {
          /* save the current state in the parent's history */
          pFsm->pHistory[pFsm->pGraph[parent].histIdx] = pFsm->currentState;
        }

        /* run the entry function of the current state */
        if(pFsm->pGraph[pFsm->currentState].entryFunc != (fsm_action_t)(0))
        {
          pFsm->pGraph[pFsm->currentState].entryFunc();
        }

        /* check if the current state has a history */
        if(pFsm->pGraph[pFsm->currentState].histIdx != NO_FSM_HISTORY && pFsm->pHistory != 0)
        {
          /* set the history state as current state */
          pFsm->currentState = pFsm->pHistory[pFsm->pGraph[pFsm->currentState].histIdx];

          /* run the entry point of the history state */
          if(pFsm->pGraph[pFsm->currentState].entryFunc != (fsm_action_t)(0))
          {
            pFsm->pGraph[pFsm->currentState].entryFunc();
          }
        }

        /* search for all child states of the current state */
        while(pFsm->pGraph[pFsm->currentState].child != NO_FSM_CHILD)
        {
          /* set the child state as the current state */
          pFsm->currentState = pFsm->pGraph[pFsm->currentState].child;

          /* check if the current state has a history */
          if(pFsm->pGraph[pFsm->currentState].histIdx != NO_FSM_HISTORY && pFsm->pHistory != 0)
          {
            pFsm->currentState = pFsm->pHistory[pFsm->pGraph[pFsm->currentState].histIdx];
          }

          /* run the entry function of the child state */
          if(pFsm->pGraph[pFsm->currentState].entryFunc != (fsm_action_t)(0))
          {
            pFsm->pGraph[pFsm->currentState].entryFunc();
          }
        }

        return((fsm_ret_t)FSM_RET_OK);
      }

      if(ActionIsFound == FSM_RET_OK)
      {
        /* execute the action */
        pTransitionAction();
        return((fsm_ret_t)FSM_RET_OK);
      }
    }

    /* search the event in all parent states */
    if((state < pFsm->nbStates) && (pFsm->pGraph[state].parent != NO_FSM_PARENT))
    {
       ChildState = state;
       state = pFsm->pGraph[state].parent;
    }
    else
    {
      return((fsm_ret_t)FSM_RET_NOK);
    }
  }
}
