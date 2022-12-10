/*******************************************************************************************************************
 * Author: Mrunal Y
 * References:Lalit Pandit's lecture slides, Dean ch7,
 * https://developer.arm.com/documentation/dui0497/a/cortex-m0-peripherals/
 * optional-system-timer--systick/systick-control-and-status-register
 * and sec B3.3 of the “ARM®v6-M Architecture Reference Manual”
 *
 * Credits : https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_2/Source/main.c
 *
 * @Credits for concepts and crafting: Lalit Pandit
 *
 * Description : contains 3 functions
 *
 ********************************************************************************************************************/

#ifndef switch_H_
#define switch_H_
/*************************************************
 * @function	: function to initialise switch
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void init_switch();

/*************************************************
 * @function	: IRQ Handler
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void PORTD_IRQHandler(void);


/*************************************************
 * @function	: button press
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
int button_pressed(void);

/*********************************************end*******************************************************************/
#endif
