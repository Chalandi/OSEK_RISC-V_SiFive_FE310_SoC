// *****************************************************************************
// Filename    : OsHwPltfm.h
// 
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 18.01.2023
// 
// Description : Hardware platform header file for SiFive RISC-V FE310 SoC
// 
// *****************************************************************************

#ifndef __HARDWARE_PLATFORM_H__
#define __HARDWARE_PLATFORM_H__

//=========================================================================================
// Includes
//=========================================================================================
#include"Platform_Types.h"
#include"OsAsm.h"

#define OS_GEN_NOT
#include"OsGenCfg.h"
#undef  OS_GEN_NOT

#include "FE310.h"
#include "riscv-csr.h"

//=========================================================================================
// Definitions
//=========================================================================================
#define osDispatch()              CLINT->msip = 1ul; __asm("FENCE.I")

#define ENABLE_INTERRUPTS()       csr_set_bits_mstatus(MSTATUS_MIE_BIT_MASK)
#define DISABLE_INTERRUPTS()      csr_clr_bits_mstatus(MSTATUS_MIE_BIT_MASK)

//=========================================================================================
// SYSTICK
//=========================================================================================
/* 64-bit access to the mtime registers */
#define MTIMECMP64  *(volatile uint64*)(&(CLINT->mtimecmp))
#define MTIME64     *(volatile uint64*)(&(CLINT->mtime))

/* macros for mtime timeout */
#define MTIME_FREQ_KHZ         (uint64)32768ull
#define MTIME_TIMEOUT_S(t)     (uint64)(MTIME_FREQ_KHZ * t)
#define MTIME_TIMEOUT_MS(t)    (uint64)((uint64)(MTIME_FREQ_KHZ * t) / 1000U)
#define MTIME_TIMEOUT_US(t)    (uint64)((uint64)(MTIME_FREQ_KHZ * t) / 1000000UL)

//=========================================================================================
// Functions Prototype
//=========================================================================================
uint32 osGetPMR(void);
void osSetPMR(uint32 level);
void osHwTimerInit(void);
void osHwTimerStart(void);
void osHwTimerReload(void);
void osRestoreSavedIntState(void);
void osSaveAndDisableIntState(void);
void OsRunSysTickIsr(void);
void OsCatchAllCpuExceptions(void);
void OsIsr_SysTickTimerFunc(void);

#endif
