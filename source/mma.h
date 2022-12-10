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
 * Description : initialise accelerometer and get values using i2c
 *
 ********************************************************************************************************************/
#ifndef MMA_H_
#define MMA_H_
/*************************************************
 * @function	: function to initialize mma8451 sensor
 *                i2c has to already be enabled
 * @parameters	: none
 * @return		: none
 *************************************************/
int init_mma();
/*************************************************
 * @function	: Function reads 6 bytes of data from sensor starting with register
                  REG_XHI.
 * @parameters	: none
 * @return		: none
 *************************************************/
void read_full();
/*************************************************
 * @function	: function to read bytes
 * @parameters	: none
 * @return		: none
 *************************************************/
void read(void);
/*************************************************
 * @function	: function to calculate tilt angle using roll pitch values from accelerometer
 * @parameters	: none
 * @return		: angle tilted
 *************************************************/
float convert_xyz_to_roll_pitch(void);

/*********************************************end*******************************************************************/
#endif
