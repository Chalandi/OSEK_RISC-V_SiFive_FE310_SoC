/******************************************************************************************
  Filename    : Mcu.c
  
  Core        : RV32IMAC
  
  MCU         : FE310-G002 (SiFive)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 11.12.2022
  
  Description : Microcontroller routine implementation
  
******************************************************************************************/

//=====================================================================================================
// Includes
//=====================================================================================================
#include "FE310.h"
#include "Clock.h"
#include "Mcu.h"
#include "riscv-csr.h"

//=====================================================================================================
// Functions prototype
//=====================================================================================================

//=====================================================================================================
// Macros
//=====================================================================================================

//=====================================================================================================
// Globals
//=====================================================================================================


//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void FE310_HwInitialization(void)
{
  /* Configure the cpu and the peripheral clocks */
  FE310_ClockInitialization();

  /* Set output high (and set value before switching to output). */
  GPIO0->output_val.bit.pin5 = 1;
  GPIO0->output_en.bit.pin5 = 1;

}
