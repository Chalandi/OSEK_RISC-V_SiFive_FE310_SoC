// *****************************************************************************
// Filename    : OsHwPltfm.c
// 
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 18.01.2023
// 
// Description : Hardware platform implementation for SiFive RISC-V FE310 SoC
// 
// *****************************************************************************

//=========================================================================================
// Includes
//=========================================================================================
#include"OsTypes.h"
#include"OsHwPltfm.h"
#include"OsInternal.h"
#include"OsTcb.h"

//=========================================================================================
// Functions Prototype
//=========================================================================================
ISR(SysTickTimer);

//=========================================================================================
// Globals
//=========================================================================================
volatile uint32 OsHwPltfmSavedIntState = 0;

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsIsInterruptContext
///
/// \descr  This function check the cpu mode (thread or interrupt).
///
/// \param  void
///
/// \return boolean: TRUE -> Cpu is in interrupt context, FALSE -> Cpu is not in interrupt context
//------------------------------------------------------------------------------------------------------------------
boolean OsIsInterruptContext(void)
{
  /* SiFive CLINT does not support nested interrupt in the HW
     OS category 1 interrupt is not supported in this architecture */
  return((OCB_Cfg.OsInterruptNestingDeepth > 0) ? TRUE : FALSE);
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
void osHwTimerInit(void)
{

}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
void osHwTimerStart(void)
{
  MTIMECMP64 = MTIME64 + MTIME_TIMEOUT_US(SYS_TICK_US_VAL);
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
void osHwTimerReload(void)
{
  MTIMECMP64 = MTIME64 + MTIME_TIMEOUT_US(SYS_TICK_US_VAL);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  osInitInterrupts
///
/// \descr  Init the cat2 interrupts
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void osInitInterrupts(void)
{
  for(uint32 IntId = 0; IntId < 53; IntId++)
  {
    if(IsrLookupTable[IntId].IsrFunc != pISR(Undefined))
    {
      /* configure the interrupt's priority */
      PLIC->priority[IntId].reg = IsrLookupTable[IntId].Prio;

      /* enable the interrupt */
      *(volatile uint64*)(PLIC->enable) |= (uint64)(1ull << IntId);
    }
    else
    {
      /* disable the interrupt */
      *(volatile uint64*)(PLIC->enable) &= ~((uint64)(1ull << IntId));
    }
  }

  /* PLIC nested interrupts are not supported */
  PLIC->threshold.reg = 0;

  /* clear all the PLIC pending flags before enabling the global external interrupt flag */
  while(PLIC->claim != 0u)
  {
    PLIC->claim = PLIC->claim;
  }

  /* set the global interrupts enable flags */
  csr_set_bits_mie(MIE_MSI_BIT_MASK | MIE_MTI_BIT_MASK | MIE_MEI_BIT_MASK);

}

//------------------------------------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void osSetPMR(uint32 level)
{
  PLIC->threshold.reg = level;
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
uint32 osGetPMR(void)
{
  return(PLIC->threshold.reg);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsRunCat2Isr
///
/// \descr  This function is the entry point of all category 2 interrupts (PLIC).
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OsRunCat2Isr(void)
{
  /* get the PLIC pending interrupt ID */
  static uint32 PlicIntId = 0;

  PlicIntId = PLIC->claim;

  if(PlicIntId < 52u)
  {
    /* call the appropriate interrupt service routine */
    IsrLookupTable[PlicIntId].IsrFunc();
  }
  else
  {
    OsKernelError(E_OS_KERNEL_PANIC);
  }

  /* clear pending interrupt flag by setting the associated enable bit */
  *(volatile uint64*)(PLIC->enable) |= (uint64)(1ull << PlicIntId);

  /* set the interrupt as completed */
  PLIC->claim = (uint32)PlicIntId;

  OCB_Cfg.OsInterruptNestingDeepth--;
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsRunSysTickIsr
///
/// \descr  System tick interrupt service routine.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OsRunSysTickIsr(void)
{
  CALL_ISR(SysTickTimer);
  OCB_Cfg.OsInterruptNestingDeepth--;
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsCatchAllCpuExceptions
///
/// \descr  This function handle all CPU exceptions.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OsCatchAllCpuExceptions(void)
{
  DISABLE_INTERRUPTS();
  for(;;);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  osSaveAndDisableIntState
///
/// \descr  This function save and disable the CPU interrupt state.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void osSaveAndDisableIntState(void)
{
  OsHwPltfmSavedIntState = csr_read_clr_bits_mstatus(MSTATUS_MIE_BIT_MASK);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  osRestoreSavedIntState
///
/// \descr  This function restore the saved CPU interrupt state.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void osRestoreSavedIntState(void)
{
  csr_write_mstatus(OsHwPltfmSavedIntState);
}