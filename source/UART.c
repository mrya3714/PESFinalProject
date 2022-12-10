/***************************************************************************************************************
 * Author: Mrunal Y
 * References:Lalit Pandit's lecture slides, Dean ch8,
 “ARM®v6-M Architecture Reference Manual”,Alexander, Dean.
  Embedded Systems Fundamentals with ARM Cortex-M Based Microcontrollers : A Practical Approach

  https://sourceware.org/newlib/libc.html#g_t_005fwrite_005fr

  https://community.nxp.com/t5/LPCXpresso-IDE-FAQs/What-are-Redlib-and-Newlib/m-p/475288
 *
 * Credits for code :  https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8/Serial-Demo
 *
 * @Credits for concepts and crafting: Lalit Pandit
 *
 * Description : contains 4 functions to initialise UART0, interrupt handler,read and write in order to tie UART code
 * in with the standard system I/O functions
 *
 ****************************************************************************************************************/
/*************************************headers and preprocessor directive********************************************/
#include "MKL25Z4.h"
#include "sysclock.h"
#include "UART.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "cbfifo.h"

/*********************************************macros****************************************************************/
#define UART_OVERSAMPLEFACTOR 16   //oversampling factor 16
#define SYS_CLOCK 24000000

cbfifo rx,tx;


/* UART0 initialization
 *
 * 1.Enables clock gating for UART0 and Port A.
 * 2. Allows access to control registers.
 * 3.Selects oscillator clock source for baud rate generator.
 * 4.Sets the oversampling factor to 16.
 * 5.Configures for eight data bits, no parity and stop bit as 2 .
 * 6.Enables the transmitter and receiver.
 * */
/*************************************************
 * @function	: function to initialize UART
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void Init_UART0(uint32_t baud_rate)
{
	uint16_t baud_rate_select;

    /*clock gating*/
	SIM->SCGC4 |= SIM_SCGC4_UART0(1);           //UART clock enable
	SIM->SCGC5 |= SIM_SCGC5_PORTA(1);          //PORT A clock enable

	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;  //disable tx rx

	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);       //set UART clock

	// Set pins to UART0 Rx and Tx
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Set pins to UART0 Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Set pins to UART0 Tx

	// Configure Baud Rate as

	// Set baud rate and oversampling ratio
	baud_rate_select = (uint16_t)((SYS_CLOCK)/(baud_rate * UART_OVERSAMPLEFACTOR));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;                         //BDH holds the upper 8 bits
	UART0->BDH |= UART0_BDH_SBR(baud_rate_select>>8);
	UART0->BDL = UART0_BDL_SBR(baud_rate_select);             //BDL holds the lower 8 bits
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLEFACTOR-1);

	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(1) | UART0_BDH_LBKDIE(0);

	UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(0) | UART0_C1_PE(0);

	// Don't invert transmit data, don't enable interrupts for errors
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
											| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

	// Clear error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);         //status register

	// Send LSB first, do not invert received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

	UART0->C2  |= UART_C2_TE(1);                     // Enable Tx
	UART0->C2  |= UART_C2_RE(1);                     // Enable Rx

	// Enable interrupts. Listing 8.11 on p. 234
	cbfifo_init(&tx);                               //create tx buffer
	cbfifo_init(&rx);	                            //create rx buffer

	NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2, or 3
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable receive interrupts but not transmit interrupts yet
	UART0->C2 |= UART_C2_RIE(1);
	}


/*************************************************
 * @function	: function to generate interrupt requests until a new character is written to UARTx_D to transmit
 *
 * @parameters	: none
 * @return		: none
 *************************************************/
void UART0_IRQHandler(void)
{
	uint8_t charac;
    if (UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK |UART_S1_FE_MASK | UART_S1_PF_MASK))
    {
	UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK | UART0_S1_FE_MASK | UART0_S1_PF_MASK;  // clear the error flags
	charac = UART0->D;                                                             // read the data register to clear RDRF
    }
    if (UART0->S1 & UART0_S1_RDRF_MASK)
    {
    	charac = UART0->D;                                   // received a character
		if (cbfifo_empty(&rx))
		{
			cbfifo_enqueue(&rx, &charac,1);
		}
	}
	if ( (UART0->C2 & UART0_C2_TIE_MASK) && (UART0->S1 & UART0_S1_TDRE_MASK) )  // transmitter interrupt enabled
	{ // tx buffer empty
	// can send another character
	if(cbfifo_dequeue(&tx, &charac, 1) == 1)
		{
		UART0->D = charac;
		}
	else
		{
		UART0->C2 &= ~UART0_C2_TIE_MASK; // queue is empty so disable transmitter interrupt
		}
	}
}


/*************************************************
 * @function	: function to write the specified bytes to stdout (handle = 1).
 *
 * @parameters	: handle,buffer and size
 * @return		: Returns -1 on error or 0 on success.
 *************************************************/
int __sys_write(int handle, char *buf, int size)
{
	if(handle == 1)
	{
	while(*buf != '\0')            // copy characters up to the null terminator
	{
	while (cbfifo_full(&tx))        // wait for space to open up
	;
	cbfifo_enqueue(&tx, buf, 1);  //enqueue to the tx buffer
    buf++;
	}
	if (!(UART0->C2 & UART0_C2_TIE_MASK))
	{
	UART0->C2 |= UART0_C2_TIE(1);    //enable tx interrupt if not already enabled
	}
	return 0;
	}
	else
	{
		return -1;						//in case of error
	}
}

/*************************************************
 * @function	: function to read one character from the serial connection and returns it.
 *
 * @parameters	: handle,buffer and size
 * @return		: Returns -1 if no data is available to be read.
 *************************************************/
int __sys_readc(void)
{
	char charac;
	if(cbfifo_dequeue(&rx,&charac,1)==1)
	{
		return charac;
	}
	else
	{
		return -1;
	}
}

/*********************************************end*******************************************************************/
