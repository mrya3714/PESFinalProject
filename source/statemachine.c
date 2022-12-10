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
 * Description : contains 3 functions to initialise, set led on and set led off
 *
 ********************************************************************************************************************/

#include "statemachine.h"
#include "pwm_LED.h"
#include "i2c.h"
#include "mma.h"
#include "sysclock.h"
#include "switch.h"
#include "Touch.h"
#include "test_cbfifo.h"
#include "cbfifo.h"
#include "UART.h"
#include "command_processor.h"
#include "line_accumulator.h"
#include "pwm_LED.h"

typedef enum
{
	Initialization,
	Zero_calibration,
    I2C_Read,
    User_input,
	User_output,
	User_feedback
}lua_states;

int count = 0;
int init_flag = 0;
volatile lua_states next_state = Initialization;
lua_states current_state;
extern int flag1;
void state_machine()
{
 while(1)
 {
   switch(next_state)
   {
   case Initialization :
       current_state = Initialization;
       init();
       if(init_flag == 1||init_flag == 3)
       {
       init();
       printf("Principle of Embedded Software Final Project Submission\r\n\n");
       printf("Please touch the sensor for calibration\r\n\n");
       next_state = Zero_calibration;
       }
       break;

    case Zero_calibration :
    current_state = Zero_calibration;
    touch_cal();
    if(init_flag == 2)
    {
    printf("Touch detected\r\n");
    next_state = User_input;
    }
    break;

    case User_input :
    current_state = User_input;
    UserInput();
    if(flag1 == 1)
    {
    next_state = I2C_Read;
    }
    break;

    case I2C_Read:
    current_state = I2C_Read;
    read_full();
    calculate();
    next_state = User_output;
    break;

    case User_output :
    current_state = User_output;
    output();
    next_state = I2C_Read;
    break;

    case User_feedback :
    current_state = User_feedback;
    if(init_flag == 3)
    {
    next_state = I2C_Read;
    }
    break;

  }
   delay(70);
 }
}

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
	set_led_colour(1, 1, 0);
    delay(1000);
	set_led_colour(0, 0, 0);
	init_flag = 1;
}

float calibrateAngle;
int value;
void touch_cal()
{
	int check_touch = 0;
	value = TSI_scan();
    if(check_touch<10)
     {
	if(value>20)
	   {
	set_led_colour(1,1,1);
    //printf("%d\r\n",value);
	read_full();
    calibrateAngle = convert_xyz_to_roll_pitch();
	printf("Calibrated = %d degrees\r\n", (int)calibrateAngle);
	init_flag = 2;
	//set_led_colour(0,0,0);
	   }
     }
}

float measuredAngle;
float relativeAngle=0;
extern int input_angle;
void calculate()
{
measuredAngle = convert_xyz_to_roll_pitch();

/*calculate relative angle wrt angle at calibration*/
      relativeAngle = measuredAngle - calibrateAngle;
	  if((int)relativeAngle>input_angle)
	      {
	        set_led_colour(0,0,1);
	      }
	  else if((int)relativeAngle==input_angle)
	      {
	        set_led_colour(0,1,0);
	        printf("Please hold on and press the switch\r\n\n");
	        delay(1000);
	      while(!button_pressed())
	        {
	        printf("You have achieved the angle\r\n\n");
	        delay(1000);
	        break;
	        }
	        init_flag = 3;

	      }
	  else
	      {
	       set_led_colour(1,0,0);
	      }
}

void output()
{
	printf("Current angle = %d degrees\r\n\n\n", (int)relativeAngle);

}
