/*******************************************************************************************************************
 * Author: Mrunal Y
 * References:Lalit Pandit's lecture slides, Dean ch7,
 * https://developer.arm.com/documentation/dui0497/a/cortex-m0-peripherals/
 * optional-system-timer--systick/systick-control-and-status-register
 * and sec B3.3 of the “ARM®v6-M Architecture Reference Manual”
 *
 * Credits :assignment2_tester.c
 *
 * @Credits for concepts and crafting: Lalit Pandit
 *
 * Description : test_cbfifo
 *
 ********************************************************************************************************************/

#ifndef _TEST_
#define _TEST_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/*************************************************
 * @function	: function to test cbfifo datatype other than str
 *************************************************/
bool test_cbfifo_str();
/*************************************************
 * @function	: function to test cbfifo
 *
 * @parameters	: none
 * @return		: 1 on success 0 on failure
 *************************************************/
int test_cbfifo();
/******************************************************
 * @function	: function to test leds
 *
 * @parameters	: none
 * @return		: none
 ******************************************************/
void test_leds();
/******************************************************
 * @function	: function to test Touch sensor
 *
 * @parameters	: none
 * @return		: none
 ******************************************************/
void test_TSI();
#endif

