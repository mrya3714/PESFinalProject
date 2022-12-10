/***************************************************************************************************************
 * Author: Mrunal Y
 * References:Lalit Pandit's lecture slides, Dean ch8,
 “ARM®v6-M Architecture Reference Manual”,Alexander, Dean.
  Embedded Systems Fundamentals with ARM Cortex-M Based Microcontrollers : A Practical Approach

  https://sourceware.org/newlib/libc.html#g_t_005fwrite_005fr

  https://community.nxp.com/t5/LPCXpresso-IDE-FAQs/What-are-Redlib-and-Newlib/m-p/475288
 *
 * Credits for code :  https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8/Serial-Demo
 *
 * @Credits for concepts and crafting: Lalit Pandit
 *
 * Description : contains 4 functions to initialise UART0, interrupt handler,read and write in order to tie UART code
 * in with the standard system I/O functions
 *
 ****************************************************************************************************************/

#ifndef UART0_H

#include <stdint.h>
#include "cbfifo.h"

/* UART0 initialization
 *
 * 1.Enables clock gating for UART0 and Port A.
 * 2. Allows access to control registers.
 * 3.Selects oscillator clock source for baud rate generator.
 * 4.Sets the oversampling factor to 16.
 * 5.Configures for eight data bits, no parity and stop bit as 2 .
 * 6.Enables the transmitter and receiver.
 * */
/*************************************************
 * @function	: function to initialize UART
 *
 * @parameters	: none
 * @return		: none
 *************************************************/

void Init_UART0(uint32_t baud_rate);

#endif
