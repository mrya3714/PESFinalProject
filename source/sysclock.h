/*****************************************************************************************************
 * sysclock.h - configuration routines for KL25Z system clock
 * 
 * Author Howdy Pierce, howdy.pierce@colorado.edu
 *******************************************************************************************************/

#ifndef _SYSCLOCK_H_
#define _SYSCLOCK_H_


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "MKL25Z4.h"
/*******************************************************************************************************
 * Initializes the system clock. You should call this first in your
 * program.
 *****************************************************************************************************/
void sysclock_init();

/*************************************************
 * @function	: function to generate delay
 *
 * @parameters	: delay time
 * @return		: none
 *************************************************/
void delay (uint32_t dleay);

#endif  // _SYSCLOCK_H_
/*********************************************end*******************************************************************/
