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

/*************************************headers and preprocessor directive********************************************/
#include <MKL25Z4.H>
#include "mma.h"
#include "i2c.h"
#include "statemachine.h"
#include <math.h>
#include "sysclock.h"

/***************************MACROS Define symbolic names **********************************************************/
#define MMA_ADDR 0x3A
#define REG_XHI 0x01
#define REG_XHI 0x01
#define REG_XLO 0x02
#define REG_YHI 0x03
#define REG_YLO 0x04
#define REG_ZHI	0x05
#define REG_ZLO 0x06

#define REG_CTRL1  0x2A
#define COUNTS_PER_G (4096.0)
#define M_PI (3.14159265)

int16_t acc_X=0, acc_Y=0, acc_Z=0;
float roll=0.0, pitch=0.0;

//mma data ready
extern uint32_t DATA_READY;

/*************************************************
 * @function	: function to initialize mma8451 sensor
 *                i2c has to already be enabled
 * @parameters	: none
 * @return		: none
 *************************************************/

int init_mma()
{
	//set active mode, 14 bit samples and 800 Hz ODR
	i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
	return 1;
}

/*************************************************
 * @function	: Function reads 6 bytes of data from sensor starting with register
                  REG_XHI.
 * @parameters	: none
 * @return		: none
 *************************************************/
void read_full()
{
	int i;
	uint8_t data[6];
	int16_t temp[3];

	i2c_start();                            //start i2c
	i2c_read_setup(MMA_ADDR , REG_XHI);     //setup read

	// Read five bytes in repeated mode
	for( i=0; i<5; i++)
	{
		data[i] = i2c_repeated_read(0);
	}
	// Read last byte ending repeated mode
	data[i] = i2c_repeated_read(1);

	for ( i=0; i<3; i++ )
	{
		temp[i] = (int16_t) ((data[2*i]<<8) | data[2*i+1]);
	}

	// Align for 14 bits
	acc_X = temp[0]/4;
	acc_Y = temp[1]/4;
	acc_Z = temp[2]/4;
}

/*************************************************
 * @function	: function to read bytes
 * @parameters	: none
 * @return		: none
 *************************************************/
void read(void)
{
	// sign extend byte to 16 bits - need to cast to signed since function
	// returns uint8_t which is unsigned
	acc_X = (int8_t) i2c_read_byte(MMA_ADDR, REG_XHI);
	Delay(100);
	acc_Y = (int8_t) i2c_read_byte(MMA_ADDR, REG_YHI);
	Delay(100);
	acc_Z = (int8_t) i2c_read_byte(MMA_ADDR, REG_ZHI);

}

/*************************************************
 * @function	: function to calculate tilt angle using roll pitch values from accelerometer
 * @parameters	: none
 * @return		: angle tilted
 *************************************************/
float convert_xyz_to_roll_pitch(void)
{
	float ax = acc_X/COUNTS_PER_G,ay = acc_Y/COUNTS_PER_G, az = acc_Z/COUNTS_PER_G;
	float tilt_angle = 0.0;

	roll = atan2(ay, az)*180/M_PI;
	pitch = atan2(ax, sqrt(ay*ay + az*az))*180/M_PI;

	tilt_angle = acos((az) / (sqrt((ax * ax) + (ay * ay) + (az * az)))) * 180/M_PI;
	return tilt_angle;

}

/*********************************************end*******************************************************************/
