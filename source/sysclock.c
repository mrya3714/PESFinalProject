/* ****************************************************************************************************************
 * sysclock.c - configuration routines for KL25Z system clock
 * 
 * Author Howdy Pierce, howdy.pierce@colorado.edu
 *
 * See section 24 of the KL25Z Reference Manual to understand this code
 *
 * Inspired by https://learningmicro.wordpress.com/configuring-device-clock-and-using-systick-system-tick-timer-module-to-generate-software-timings/
               https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/src/delay.c
 ********************************************************************************************************************/

#include "MKL25Z4.h"
#include "sysclock.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define SYSCLOCK_FREQUENCY (24000000U)

void sysclock_init()
{
  // Corresponds to FEI mode as shown in sec 24.4.1 

  // Select PLL/FLL as clock source 
  MCG->C1 &= ~(MCG_C1_CLKS_MASK);
  MCG->C1 |= MCG_C1_CLKS(0);
	
  // Use internal reference clock as source for the FLL
  MCG->C1 |= MCG_C1_IREFS(1);

  // Select the FLL (by setting "PLL select" to 0)
  MCG->C6 &= ~(MCG_C6_PLLS_MASK);
  MCG->C6 |= MCG_C6_PLLS(0);

  // Select 24 MHz - see table for MCG_C4[DMX32]
  MCG->C4 &= ~(MCG_C4_DRST_DRS_MASK & MCG_C4_DMX32_MASK);
  MCG->C4 |= MCG_C4_DRST_DRS(0);
  MCG->C4 |= MCG_C4_DMX32(1);

}

/*************************************************
 * @function	: function to generate delay
 *
 * @parameters	: delay time
 * @return		: none
 *************************************************/
void delay (uint32_t dleay) {
  volatile uint32_t time;

	for (time=dleay*10000; time>0; time--)
		;
}
/*********************************************end*******************************************************************/
