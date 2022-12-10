/************************************************************************************************************
 * Author: Mrunal Y
 * References:Lalit Pandit's lecture slides, Dean ch8,
 “ARM®v6-M Architecture Reference Manual”,Alexander, Dean.
  Embedded Systems Fundamentals with ARM Cortex-M Based Microcontrollers : A Practical Approach

 *  Credits for code : https://linuxhint.com/string-integer-c/
 *
 * @Credits for concepts and crafting: Lalit Pandit
 *
 * Description : contains 2 functions to accumulate a line and passes the line buffer to process the message and
 *               handle input
 *
 ************************************************************************************************************/

/*************************************headers and preprocessor directive********************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include "cbfifo.h"
#include "line_accumulator.h"
#include "command_processor.h"

extern cbfifo rx,tx;


/*************************************************
 * @function	: line accumulator
 *
 * @parameters	: pointer to buffer
 * @return		: none
 *
 * Description :  1.read the incoming bytes
 *                2.accumulate into a line buffer
 *                3.echo char back to other side
 *************************************************/
void line_accumulator(char *ptr_buf)
{
	char input;
    char line_buffer[100]={0};                 //input line buffer
	*ptr_buf = &line_buffer[0];          //pointer initialized to 0th index of line buffer
	while(1)
	{
		while(cbfifo_length(&rx) == 0)
		 {
			;                          //wait for rx to be empty for further commands
		 }

		cbfifo_dequeue(&rx, &input, 1); //dequeue the input

		putchar(input);

		if(input == '\r')               //sets the cursor at the start of the current line.
		 {
			input = '\n';
			printf("%c",input);      //print the input
			break;
		 }

		*ptr_buf = input;
		ptr_buf++;
	    *ptr_buf = '\0';            //terminate
	}

	//command_processor(line_buffer);		//Process input into a series of tokens
}

/*************************************************
 * @function	: function to handle user input convert character to integer
 *
 * @parameters	: none
 * @return		: none
 *************************************************/

int flag1 = 0;
int input_angle;
void UserInput()
{
	printf("\r\nPlease input desired angle in degrees(0-180 deg): \r\n");

	int ibuf_size = 150;
	char i_str[ibuf_size];
	char *ptr;

	line_accumulator(i_str);          //print the input

	/*convert the string input value to integer type*/
	input_angle = strtol(i_str, &ptr, 10);
	printf("Input Angle is %ld degrees\r\n", input_angle); //print the input angle
	if(input_angle<=180)               //if the input angle is <= 180 next process will be initiated
	{
    flag1 = 1;
	}
	else                              //else user will be asked for the input again
	{
	UserInput();
	}

}

/*********************************************end*******************************************************************/
