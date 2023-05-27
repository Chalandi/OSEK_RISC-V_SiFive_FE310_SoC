
/*******************************************************************************************************************
** Includes
*******************************************************************************************************************/
#include"OsTcb.h"
#include"OsAPIs.h"
#include "FE310.h"
#include "riscv-csr.h"

#define TOGGLE_BLUE_LED()\
{\
  csr_clr_bits_mip((uint32)-1);\
  GPIO0->output_val.bit.pin5 ^= 1;\
}

#define TURN_ON_LED_BLUE()\
{\
  csr_clr_bits_mip((uint32)-1);\
  GPIO0->output_val.bit.pin5 = 1;\
}

TASK(T1)
{
  TURN_ON_LED_BLUE();

  const OsEventMaskType OsWaitEventMask = (OsEventMaskType) EVT_BLINK_BLUE_LED;

  (void)OS_SetRelAlarm(ALARM_BLUE_LED, 0, 997);

  for(;;)
  {
    OsEventMaskType Events = (OsEventMaskType) 0U;

    if(E_OK == OS_WaitEvent(OsWaitEventMask))
    {
      (void) OS_GetEvent((OsTaskType)T1, &Events);

      if((Events & EVT_BLINK_BLUE_LED) == EVT_BLINK_BLUE_LED)
      {
        OS_ClearEvent(EVT_BLINK_BLUE_LED);
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
  for(;;)
  {
    OS_Schedule();
  }
}
