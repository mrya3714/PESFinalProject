/*******************************************************************************************************************
 * Author: Mrunal Y
 * References:Lalit Pandit's lecture slides, Dean ch8,
 * https://developer.arm.com/documentation/dui0497/a/cortex-m0-peripherals/
 * optional-system-timer--systick/systick-control-and-status-register
 * and sec B3.3 of the “ARM®v6-M Architecture Reference Manual”
 *
 * Credits : https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/src/i2c.c
 *           https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/src/mma8451.c
 *           https://community.nxp.com/t5/Sensors-Knowledge-Base/MMA8451Q-Bare-metal-example-project/ta-p/1127268
             https://mwrona.com/posts/accel-roll-pitch/
             https://www.analog.com/en/app-notes/an-1057.html
             https://community.nxp.com/t5/Kinetis-Microcontrollers/MMA8451-on-kl25z-baremetal-code-angle-calculation
                    /td-p/288270
 *
 * @Credits for concepts and crafting: Lalit Pandit
 *
 ********************************************************************************************************************/
#ifndef SM_H_
#define SM_H_

/*************************************************
 * @function	: function for state machine and api call
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void state_machine();
/*************************************************
 * @function	: function to initialize leds, tsi, i2c, sysclock, UART
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void init();
/*************************************************
 * @function	: function to calculate current angle and glow leds accordingly
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void calculate();
/*************************************************
 * @function	: function to display on the terminal current angle
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void output();
/*************************************************
 * @function	: function to calibrate angle using touch slider
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void touch_cal();

#endif
/*********************************************end*******************************************************************/
