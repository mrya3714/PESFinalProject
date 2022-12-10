/*******************************************************************************************************************
 * Author: Mrunal Y
 * References:Lalit Pandit's lecture slides, Dean ch7,
 * https://developer.arm.com/documentation/dui0497/a/cortex-m0-peripherals/
 * optional-system-timer--systick/systick-control-and-status-register
 * and sec B3.3 of the “ARM®v6-M Architecture Reference Manual”
 *
 * Credits : https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_2/Source/main.c
 * Credits : https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense
 *           https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/src/LEDs.c
 *
 * @Credits for concepts and crafting: Lalit Pandit
 *
 * Description : contains 3 functions to initialise, set led on and set led off
 *
 ********************************************************************************************************************/

/*************************************headers and preprocessor directive********************************************/
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "pwm_LED.h"

/***************************Define symbolic names for the LED port bits*********************************************/
#define R_LED_PIN 18
#define G_LED_PIN 19
#define B_LED_PIN 1

#define MASK(x) (1UL << (x))

/*************************************************
 * @function	: function to initialize LEDs
 *
 * @parameters	: none
 * @return		: none
 *************************************************/

void init_led()
{
/*Enable clock signal to Port B by setting bits 10 and 12 in the SIM’s SCGC5 register*/
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;                    //Enable clock signal to Port B
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;	        		   //Enable clock signal to Port D

/*Select pin MUX mode to GPIO by setting the MUX field of Port B and D to 001(make 3 pins GPIO)*/
    PORTB->PCR[R_LED_PIN] &= ~PORT_PCR_MUX_MASK;           //Red LED
    PORTB->PCR[R_LED_PIN] |= PORT_PCR_MUX(1);

    PORTB->PCR[G_LED_PIN] &= ~PORT_PCR_MUX_MASK;           //Green LED
    PORTB->PCR[G_LED_PIN] |= PORT_PCR_MUX(1);

    PORTD->PCR[B_LED_PIN] &= ~PORT_PCR_MUX_MASK;           //Blue LED
    PORTD->PCR[B_LED_PIN] |= PORT_PCR_MUX(1);

/*Define the port bits to output*/
    GPIOB->PDDR |= MASK(R_LED_PIN);
    GPIOB->PDDR |= MASK(G_LED_PIN);
    GPIOD->PDDR |= MASK(B_LED_PIN);

/*Turn off all the leds*/
    GPIOB->PSOR |= MASK(R_LED_PIN);
    GPIOB->PSOR |= MASK(G_LED_PIN);
    GPIOD->PSOR |= MASK(B_LED_PIN);

}


/*************************************************
 * @function	: function to set LEDs colors, Function takes input as an integer.
 *                for Red Green and Blue LED
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void set_led_colour(int red,int green,int blue) {
	if (red == 1)
	{
			PTB->PCOR = MASK(R_LED_PIN);
	} else
	{
			PTB->PSOR = MASK(R_LED_PIN);
	}
	if (green == 1)
	{
			PTB->PCOR = MASK(G_LED_PIN);
	}	else
	{
			PTB->PSOR = MASK(G_LED_PIN);
	}
	if (blue == 1)
	{
			PTD->PCOR = MASK(B_LED_PIN);
	}	else
	{
			PTD->PSOR = MASK(B_LED_PIN);
	}
}

/*************************************************
 * @function	: function to turn off the LEDs, takes boolean as parameter if true it will turn of all the leds
 *
 * @parameters	: none
 * @return		: none
 *************************************************/

void set_led_off(bool state)
{
    if(state)
    {
    GPIOB->PSOR |= (1 << R_LED_PIN);
    GPIOB->PSOR |= (1 << G_LED_PIN);
    GPIOD->PSOR |= (1 << B_LED_PIN);
    }
}
/*********************************************end*******************************************************************/
