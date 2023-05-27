
/*******************************************************************************************************************
** Includes
*******************************************************************************************************************/
#include"OsTcb.h"
#include"OsAPIs.h"
#include "FE310.h"
#include "riscv-csr.h"

#define TOGGLE_BLUE_LED()\
{\
  OS_DisableAllInterrupts();\
  csr_clr_bits_mip((uint32)-1);\
  GPIO0->output_val.bit.pin5 ^= 1;\
  OS_EnableAllInterrupts();\
}

#define TURN_ON_LED_BLUE()\
{\
  OS_DisableAllInterrupts();\
  csr_clr_bits_mip((uint32)-1);\
  GPIO0->output_val.bit.pin5 = 1;\
  OS_EnableAllInterrupts();\
}

TASK(T1)
{
  TURN_ON_LED_BLUE();

  const OsEventMaskType OsWaitEventMask = (OsEventMaskType) EVT_BLINK_LED;

  (void)OS_SetRelAlarm(ALARM_BLINK_LED, 0, 997);

  for(;;)
  {
    OsEventMaskType Events = (OsEventMaskType) 0U;

    if(E_OK == OS_WaitEvent(OsWaitEventMask))
    {
      (void) OS_GetEvent((OsTaskType)T1, &Events);

      if((Events & EVT_BLINK_LED) == EVT_BLINK_LED)
      {
        OS_ClearEvent(EVT_BLINK_LED);
        TOGGLE_BLUE_LED();
      }
    }
    else
    {
      OS_TerminateTask(); /* In case of error we switch off the task */
    }
  }
}

TASK(Idle)
{
  const OsEventMaskType OsWaitEventMask = (OsEventMaskType) EVT_DUMMY_LED;

  (void)OS_SetRelAlarm(ALARM_DUMMY_LED, 0, 503);

  for(;;)
  {
    OS_Schedule();

    OsEventMaskType Events = (OsEventMaskType) 0U;

    if(E_OK == OS_WaitEvent(OsWaitEventMask))
    {
      (void) OS_GetEvent((OsTaskType)Idle, &Events);

      if((Events & EVT_DUMMY_LED) == EVT_DUMMY_LED)
      {
        OS_ClearEvent(EVT_DUMMY_LED);
      }
    }
    else
    {
      OS_TerminateTask(); // In case of error we switch off the task
    }
  }
}
