// **********************************************************************************************************************
//                                                  OSEK OS Configuration                                                
// **********************************************************************************************************************

// **********************************************************************************************************************
// Filename        : osGenCfg.h
// 
// Author          : Chalandi Amine
//
// Owner           : Chalandi Amine
// 
// Date            : 14.01.2023
// 
// Description     : OS Configuration file
// 
// **********************************************************************************************************************

#include "OsGenMac.h"

//=============================================================================
// OS Configuration
//=============================================================================

OS_CONFIG_BEGIN

  OS_TASK_BEGIN
    OS_TASK_DEF(Idle, 1, 1024, 1, OS_AUTOSTART, EXTENDED, FULL_PREEMPT)
    OS_TASK_DEF(T1, 4, 1024, 1, OS_AUTOSTART, EXTENDED, FULL_PREEMPT)
  OS_TASK_END

  OS_EVENT_BEGIN
    OS_EVENT_DEF(EVT_BLINK_BLUE_LED, (1UL << 0))
  OS_EVENT_END

  OS_ALARM_BEGIN
    OS_ALARM_DEF(ALARM_BLUE_LED, ALARM_SET_EVENT, EVT_BLINK_BLUE_LED, T1, 0)
  OS_ALARM_END

  OS_RESOURCE_BEGIN
    OS_RESOURCE_DEF(RES_SCHEDULER, RES_SCHEDULER_PRIO, { 1,1 })
  OS_RESOURCE_END

  //=============================================================================
  //  EI Interrupts Configuration
  //=============================================================================

  OS_INTERRUPT_BEGIN
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 00  Reserved  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 01  WATCHDOG  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 02  RTC       */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 03  UART0     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 04  UART1     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 05  QSPI0     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 06  QSPI1     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 07  QSPI2     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 08  GPIO0     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 09  GPIO1     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 10  GPIO2     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 11  GPIO3     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 12  GPIO4     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 13  GPIO5     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 14  GPIO6     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 15  GPIO7     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 16  GPIO8     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 17  GPIO9     */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 18  GPIO10    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 19  GPIO11    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 20  GPIO12    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 21  GPIO13    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 22  GPIO14    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 23  GPIO15    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 24  GPIO16    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 25  GPIO17    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 26  GPIO18    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 27  GPIO19    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 28  GPIO20    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 29  GPIO21    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 30  GPIO22    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 31  GPIO23    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 32  GPIO24    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 33  GPIO25    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 34  GPIO26    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 35  GPIO27    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 36  GPIO28    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 37  GPIO29    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 38  GPIO30    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 39  GPIO31    */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 40  PWM0CMP0  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 41  PWM0CMP1  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 42  PWM0CMP2  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 43  PWM0CMP3  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 44  PWM1CMP0  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 45  PWM1CMP1  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 46  PWM1CMP2  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 47  PWM1CMP3  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 48  PWM2CMP0  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 49  PWM2CMP1  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 50  PWM2CMP2  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 51  PWM2CMP3  */
    OS_INTERRUPT_CAT2_DEF(Undefined, 0, NOT_NESTED)   /* IRQ 52  I2C0      */
  OS_INTERRUPT_END

  //=============================================================================
  //  Hooks Configuration
  //=============================================================================
  #define STARTUPHOOK            0
  #define ERRORHOOK              0
  #define SHUTDOWNHOOK           0
  #define PRETASKHOOK            0
  #define POSTTASKHOOK           0

  //=============================================================================
  //  Interrupt Configuration
  //=============================================================================
  #define FE_INTERRUPT           0
  #define INTERRUPT              1

  //=============================================================================
  //  Clock Configuration
  //=============================================================================
  #define SYS_TICK_US_VAL        1000U

  //=============================================================================
  //  Interrupt Mask Configuration
  //=============================================================================
  #define OS_CAT1_PRIO_MASK       0U

OS_CONFIG_END
