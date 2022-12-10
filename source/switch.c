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
/*************************************headers and preprocessor directive********************************************/
#include "switch.h"
#include "MKL25Z4.h"

/***************************MACROS Define symbolic names **********************************************************/
#define    GPIO_PIN             (3)                         //Gpio pin 3
#define    SWITCH_GPIO_PORT     (GPIOD)                     //GPIO Port D

static volatile int b_press = 0;  //To keep track of button press

/*************************************************
 * @function	: function to initialise switch
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void init_switch(){

	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;                            //Sourcing clock to port D

	PORTD->PCR[GPIO_PIN] &= ~PORT_PCR_MUX_MASK;                    //Setting the PCR Value
	PORTD->PCR[GPIO_PIN] |= PORT_PCR_MUX(1);                       // multiplexing the pin to GPIO

	PORTD->PCR[GPIO_PIN] |= PORT_PCR_PE(1) | PORT_PCR_PS(1);       //Enable the pull-up

	SWITCH_GPIO_PORT->PDDR &= ~(1 << GPIO_PIN);                //Clear port data direction register for switch

	PORTD->PCR[GPIO_PIN] |= PORT_PCR_IRQC(8);                  //Interrupt on logic LOW


	NVIC_SetPriority (PORTD_IRQn, 3);
	NVIC_EnableIRQ(PORTD_IRQn);                               // Enabling the interrupt

}


/*************************************************
 * @function	: IRQ Handler
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void PORTD_IRQHandler(void)
{

	if ( ( (PORTD->ISFR) & (1 << GPIO_PIN) ) == 0)
		return;
	b_press = 1;  //SET if switch is pressed

	PORTD->ISFR &= (1 << GPIO_PIN);  //Clear Interrupt status flag
}



/*************************************************
 * @function	: button press
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
int button_pressed(void){

		uint32_t masking_state = __get_PRIMASK();
		__disable_irq();               //to avoid race

		int ret = b_press;
		b_press = 0;         //reset global variable after reading button status

		__set_PRIMASK(masking_state); //Enable interrupt state
		return ret;
}
