/******************************************************************************************
  Filename    : boot.s
  
  Core        : RV32IMAC
  
  MCU         : FE310-G002 (SiFive)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 04.06.2021
  
  Description : boot routine 

******************************************************************************************/

.file "boot.s"

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .text
.type _start, @function
.align 4
.extern __STACK_TOP
.extern _VectoredInterruptVectorTable
.extern Startup_Init
.globl _start

_start:
        /* disable all interrupts flag */
        csrrs x0, mstatus, x0

        /* disable all specific interrupt sources */
        csrrs x0, mie, x0

        /* setup the stack pointer */
        la sp, __STACK_TOP
       
        /* setup the direct interrupt handler */
        la t0, _VectoredInterruptVectorTable
        addi t0, t0, 1
        csrrs x0, mtvec, t0

        jal   Startup_Init

.size _start, .-_start

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .text.vivt
.type _VectoredInterruptVectorTable, @function
.align 4
.globl Isr_MachineSoftwareInterrupt
.globl Isr_MachineTimerInterrupt
.globl Isr_MachineExternalInterrupt

_VectoredInterruptVectorTable:
                               j OsCatchAllCpuExceptions  /* Exception level */
                               j Isr_UndefinedHandler
                               j Isr_UndefinedHandler
                               j OsDispatchHandler        /* MachineSoftwareInterrupt (MSI) */
                               j Isr_UndefinedHandler
                               j Isr_UndefinedHandler
                               j Isr_UndefinedHandler
                               j OsSysTickIsrWrapper      /* MachineTimerInterrupt (MTI) --> The lowest priority interrupt level */
                               j Isr_UndefinedHandler
                               j Isr_UndefinedHandler
                               j Isr_UndefinedHandler
                               j OsCat2IsrWrapper         /* MachineExternalInterrupt (MEI) --> The highest priority interrupt level */


.size _VectoredInterruptVectorTable, .-_VectoredInterruptVectorTable

.section .text
.type Isr_UndefinedHandler, @function
.align 4
Isr_UndefinedHandler: j Isr_UndefinedHandler
.size Isr_UndefinedHandler, .-Isr_UndefinedHandler



.section .text
.type Isr_ExceptionsHandler, @function
.align 4
Isr_ExceptionsHandler: j Isr_ExceptionsHandler
.size Isr_ExceptionsHandler, .-Isr_ExceptionsHandler

