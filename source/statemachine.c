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

#include <test.h>
#include "statemachine.h"
#include "pwm_LED.h"
#include "i2c.h"
#include "mma.h"
#include "sysclock.h"
#include "switch.h"
#include "Touch.h"
#include "cbfifo.h"
#include "UART.h"
#include "line_accumulator.h"
#include "pwm_LED.h"

/*states for levelling using accelerometer*/
typedef enum
{
	Initialization,
	Testing,
	Zero_calibration,
    I2C_Read,
    User_input,
	User_output
}lua_states;

int init_flag = 0;                       //initialization flag
int test_flag = 0;                       //testing flag
int touch_flag = 0;                      //touch flag

extern int flag1;                        //user input flag

volatile lua_states next_state = Initialization;
lua_states current_state;
/*************************************************
 * @function	: function for state machine and api call
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void state_machine()
{
 while(1)
 {
   switch(next_state)
   {
    case Initialization :
    current_state = Initialization;
    init();                                 //calls initialization function
    if(init_flag == 1)                      //if successful yellow led will glow or red if unsuccessful
      {
      printf("Principle of Embedded Software Final Project Submission\r\n\n");
      set_led_colour(1, 1, 0);               //red led
      delay(1000);
      set_led_off(true);                     //turn off after 1 s
      next_state =Testing;
      }
    else
    {
      set_led_colour(1, 0, 0);               //yellow led
    }
    break;
/*NOTE : These are automated test cases fucntions, manual test cases functions are included in test.c*/
    case Testing:
    test_cbfifo();                          //test cbfifos
    test_cbfifo_str();
    test_leds();                            //test leds
    if(test_flag == 3)                      //if the testing is successful user will be asked to calibrate using TSI
    {
    printf("Please touch the sensor for calibration\r\n\n");
    current_state = Testing;
    next_state = Zero_calibration;
    }
    break;

    case Zero_calibration :
    current_state = Zero_calibration;
    touch_cal();                         //calibrate the angle
    if(touch_flag == 1)
    {
    printf("Touch detected\r\n");
    next_state = User_input;
    }
    break;

    case User_input :
    current_state = User_input;
    UserInput();                      //user will be asked to input desired angle
    if(flag1 == 1)
    {
    next_state = I2C_Read;
    }
    break;

    case I2C_Read:
    current_state = I2C_Read;
    read_full();                     //i2c
    calculate();                     //calculate the current angle w.r.t input angle
    next_state = User_output;
    break;

    case User_output :
    current_state = User_output;
    output();                        //display the output current angle
    next_state = I2C_Read;
    break;

  }
   delay(70);                        //delay for visibility on terminal
 }
}
/*************************************************
 * @function	: function to initialize leds, tsi, i2c, sysclock, UART
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void init()
{
	init_led();
	TSI_init();
	i2c_init();                                         //init i2c
	sysclock_init();
	Init_UART0(38400);                                  //initialize the UART with baud rate 38400
    if (!init_mma())
	 {										            // init mma peripheral
	set_led_colour(1, 0, 0);							//Light red error LED
	while (1)								            //not able to initialize mma
	;
	}
	init_flag = 1;
}

float calibrated_angle;
int value;
/*************************************************
 * @function	: function to calibrate angle using touch slider
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void touch_cal()
{
	int check_touch = 0;
	value = TSI_scan();
    if(check_touch<10)
     {
	if(value>20)
	   {
	set_led_colour(1,1,1);
	read_full();
	calibrated_angle = convert_xyz_to_roll_pitch();
	printf("Calibrated = %d degrees\r\n", (int)calibrated_angle);
	touch_flag = 1;
	   }
     }
}

float new_angle;
float current_angle=0.0;
extern int input_angle;
/*************************************************
 * @function	: function to calculate current angle and glow leds accordingly
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void calculate()
{
	new_angle = convert_xyz_to_roll_pitch();

/*calculate current angle wrt angle at calibration*/
	current_angle = new_angle - calibrated_angle;
	  if((int)current_angle>input_angle)   //if current angle is greater than the input angle
	      {
	        set_led_colour(0,0,1);         //blue led will glow
	      }
	  else if((int)current_angle==input_angle) //if equal
	      {
	        set_led_colour(0,1,0);          //green led
	        printf("Hold on and press the switch\r\n\n");
	        delay(1000);
	      while(!button_pressed())          //switch interrupt
	        {
	        printf("You have achieved the angle\r\n\n");
	        delay(1000);
	        break;
	        }
	      }
	  else
	      {
	       set_led_colour(1,0,0);          //red led if the angle is less
	      }
}
/*************************************************
 * @function	: function to display on the terminal current angle
 *
 * @parameters	: none
 * @return		: none
 *************************************************/

void output()
{
	printf("Current angle = %d degrees\r\n\n\n", (int)current_angle);  //display current angle

}
/*********************************************end*******************************************************************/
