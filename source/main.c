/**********************************************************************************************************
 * main.c - application entry point
 * 
 * Author: Mrunal Y
 * References:Lalit Pandit's lecture slides, Dean ch8,
 “ARM®v6-M Architecture Reference Manual”,Alexander, Dean.
  Embedded Systems Fundamentals with ARM Cortex-M Based Microcontrollers : A Practical Approach
 *
 * Credits for code :  https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8/Serial-Demo
 *
 * @Credits for concepts and crafting: Lalit Pandit
 *
 * Description : calls statemachine
 *
 ***********************************************************************************************************/

#include "sysclock.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "MKL25Z4.h"
#include "test_cbfifo.h"
#include "cbfifo.h"
#include "UART.h"
#include "command_processor.h"
#include "line_accumulator.h"
#include "statemachine.h"
#include "Touch.h"
#include "pwm_LED.h"


int main(void)
{
  	state_machine();
}
