/*******************************************************************************************************************
 * Author: Mrunal Y
 * References:Lalit Pandit's lecture slides
 * @Credits for concepts and crafting: Lalit Pandit
 *
 * Credits : https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_2/Source/main.c
 * Credits : https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense
 *
 ****************************************************************************************************************/

#ifndef TOUCH_H_
#define TOUCH_H_

/*********************************************function declarations**************************************************/

/******************************************************
 * @function	: function to initialize Touch sensor
 *
 * @parameters	: none
 * @return		: none
 ******************************************************/
void TSI_init();

/*****************************************************
 * @function	: function to scan for the values and return slider values
 *
 * @parameters	: none
 * @return		: slider scan value after offset calculation
 ****************************************************/

int TSI_scan();
/*********************************************end*******************************************************************/


#endif
