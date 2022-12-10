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
 *
 * @Credits for concepts and crafting: Lalit Pandit
 *
 * Description :  Description : I2C init,read, write byte
 *
 ********************************************************************************************************************/
#ifndef i2c_H_
#define i2c_H_

void i2c_init(void);
void i2c_busy(void);
void i2c_wait(void);
void i2c_start();
void i2c_read_setup(uint8_t dev, uint8_t address);
uint8_t i2c_repeated_read(uint8_t isLastRead);
uint8_t i2c_read_byte(uint8_t dev, uint8_t address);
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);

/*********************************************end*******************************************************************/
#endif
