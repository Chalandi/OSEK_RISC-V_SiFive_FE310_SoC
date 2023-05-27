/******************************************************************************************
  Filename    : mtimer.c
  
  Core        : RV32IMAC
  
  MCU         : FE310-G002 (SiFive)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 11.12.2022
  
  Description : mtimer driver implementation
  
******************************************************************************************/

//=========================================================================================
// Includes
//=========================================================================================
#include "mtimer.h"
#include "riscv-csr.h"
#include "OsAPIs.h"

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void mtimer_ReloadTimer(uint64 timeout)
{
  OS_SuspendAllInterrupts();

  /* set the reload value */
  MTIMECMP64 = MTIME64 + timeout;

  OS_ResumeAllInterrupts();
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void mtimer_StartTimer(uint64 timeout)
{
  OS_SuspendAllInterrupts();

  const volatile uint64 next_TimeoutMark = MTIME64 + timeout;

  /* configure the timer counters */
  MTIMECMP64 = next_TimeoutMark;

  /* enable the timer interrupt */
  csr_set_bits_mie(MIE_MTI_BIT_MASK);

  OS_ResumeAllInterrupts();
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void mtimer_StopTimer(void)
{
  OS_SuspendAllInterrupts();

  /* stop the timer (will never overflow) */
  MTIMECMP64 = (uint64)-1;

  OS_ResumeAllInterrupts();
}
