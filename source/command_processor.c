/*Author: Mrunal Y
 * References:Lalit Pandit's lecture slides, Dean ch8,
 “ARM®v6-M Architecture Reference Manual”,Alexander, Dean.
  Embedded Systems Fundamentals with ARM Cortex-M Based Microcontrollers : A Practical Approach

  https://embeddedartistry.com/blog/2019/02/18/using-custom-build-steps-with-eclipse-auto-generated-makefiles/
 *
 * @Credits for concepts and crafting: Lalit Pandit
 *
 * Description :contains functions for lexical analysis and process the commands.
 *
 */
#include "command_processor.h"
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include "cbfifo.h"

static void handle_Author(int argc, char *argv[]);
static void handle_Help(int argc, char *argv[]);
static void handle_Info(int argc, char *argv[]);

typedef void (*command_handler_t)(int, char *argv[]); //function pointer

typedef struct                                        //command handler structure
{
	const char *name;
	command_handler_t handler;
	const char *help_string;
}command_table_t;

/*Look-up table
 *
 * This table consists of the function name and
 * function handle
 * */

static const command_table_t cmd[] =
{// TODO: fill out command table here
		{"author", handle_Author, "Prints author's name\r\n"},
		{"help", handle_Help, "Prints all the commands in the table\r\n"},
		{"info", handle_Info, "Prints info\r\n"}
};

/*table size of the command handler*/
static const int num_commands = sizeof(cmd)/sizeof(command_table_t);

/*function for lexical analysis and process the commands.
1.Process input into a series of tokens
2.All tokens are separated by whitespace characters
3.Lookup first token in a table of functions
4.Dispatch to handler function
*/
void command_processor(char *input)
{
	char *p = &input;
	char *end;
	bool flag = false;      //flag for unknown_command

	//To find the end pointer
	for(end = input; *end != '\0'; end++);

	//Tokenize input in place
	bool in_token = false;
	char *argv[10];
	int argc = 0;
	memset(argv, 0, sizeof(argv));		//initializing argv with 0

	for(p = input; p < end; p++)
	{
	if(*p == ' ')
	{                                 //tokens are seperated by white characters
	if(in_token==false)
	{
	*p = ' ';
	}
	else
	{
	*p = '\0';			//if the character is white space
	}
	}
	else
	{
	if(in_token==false)
    {
	argv[argc] = p;			//point to the buffer
	argc++;						//increment
	}
	in_token = true;
	}
	}
	argv[argc] = NULL;
	if (argc == 0){						//No command entered
		return;
	}

	//TODO: Dispatch argc/argv to handler
	for(int i=0; i<num_commands; i++)
	{
		if(strcasecmp(argv[0], cmd[i].name) == 0)
		{
			cmd[i].handler(argc, argv);					//calls the command parser
			flag = true;                                //set the flag as true
			return;
		}
	}

    if(flag == false)
    {
    	printf("Unknown Command: %s\r\n", argv[0]);
    }
	return;
}

/*function prints the author name, argc is the number of arguments and pointer to the array of arguments*/
static void handle_Author(int argc, char *argv[])
{
	printf("\rMrunal Yadav\r\n");
}

/*function prints the help info, argc is the number of arguments and pointer to the array of arguments*/
static void handle_Help(int argc, char *argv[])
{
	printf("Please use the below command list\r\n");
	printf("1.Author's name : prints the name of the author\r\n");
	printf("2.Help : prints the info of the commands\r\n");
	printf("3.Info: prints version and date\r\n");
}

static void handle_Info(int argc, char *argv[])
{
	printf("Version 1.0 \r\n");
	printf("2020-11-13 \r\n");
	printf("gk58e68fa52fb6e7258998aed343af3477746079\r\n");
}

