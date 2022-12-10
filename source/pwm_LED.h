/*******************************************************************************************************************
 * Author: Mrunal Y
 * References:Lalit Pandit's lecture slides
 * @Credits for concepts and crafting: Lalit Pandit
 *                                     https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code
 *                                     /Chapter_8/I2C-Demo/src/LEDs.c
 ******************************************************************************************************************/

/*********************************headers and preprocessor directive************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "MKL25Z4.h"

#ifndef Pwm_LED_H_
#define Pwm_LED_H_

/*********************************function declarations************************************************************/

/*************************************************
 * @function	: function to initialize LEDs
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void init_led();

/*************************************************
 * @function	: function to set LEDs colors
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void set_led_colour(int red,int green,int blue);

/*************************************************
 * @function	: function to turn off the LEDs
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void set_led_off(bool state);

/*********************************************end*******************************************************************/
#endif










