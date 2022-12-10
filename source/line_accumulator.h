/************************************************************************************************************
 * Author: Mrunal Y
 * References:Lalit Pandit's lecture slides, Dean ch8,
 “ARM®v6-M Architecture Reference Manual”,Alexander, Dean.
  Embedded Systems Fundamentals with ARM Cortex-M Based Microcontrollers : A Practical Approach
 *
 * @Credits for concepts and crafting: Lalit Pandit
 *
 * Description : contains 2 functions to accumulate a line and passes the line buffer to process the message and
 *               handle input
 *
 ************************************************************************************************************/

#ifndef LA_H_
#define LA_H_

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include "cbfifo.h"

/*************************************************
 * @function	: line accumulator
 *
 * @parameters	: pointer to buffer
 * @return		: none
 *
 * Description :  1.read the incoming bytes
 *                2.accumulate into a line buffer
 *                3.echo char back to other side
 *************************************************/
void line_accumulator();

/*************************************************
 * @function	: function to handle user input convert character to integer
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void UserInput();

#endif
/*********************************************end*******************************************************************/
