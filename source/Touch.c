/****************************************************************************************************************
 * Author: Mrunal Y
 * References:Lalit Pandit's lecture slides
 * @Credits for concepts and crafting: Lalit Pandit
 *
 * Credits : https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_2/Source/main.c
 * Credits : https://github.com/alexander-g-dean/ESF/tree/master/NXP/Misc/Touch%20Sense
 *****************************************************************************************************************/
/********************************************headers and preprocessor directive***********************************/

#include <stdio.h>
#include "MKL25Z4.h"
#include "Touch.h"

/*********************************************macros****************************************************************/

#define TOUCH_DATA ((TSI0->DATA) & 0xFFFF)        //macro for extracting the count from data register
#define TOUCH_OFFSET 574                          //Offset value of touch sensor

/******************************************************
 * @function	: function to initialize Touch sensor
 *
 * @parameters	: none
 * @return		: none
 ******************************************************/
void TSI_init()
{
    SIM->SCGC5 |= SIM_SCGC5_TSI_MASK; 			// enabling the clock

    TSI0->GENCS = TSI_GENCS_MODE(0u) | 			//operating in non-noise mode
    TSI_GENCS_REFCHRG(0u) | 					//reference oscillator charge and discharge value 500nA
    TSI_GENCS_DVOLT(0u) | 						//oscillator voltage rails set to default
    TSI_GENCS_EXTCHRG(0u) |		 				//electrode oscillator charge and discharge value 500nA
    TSI_GENCS_PS(0u) |  						// frequency clock divided by one
    TSI_GENCS_NSCN(31u) | 						//scanning the electrode 32 times
    TSI_GENCS_TSIEN_MASK | 						//enabling the TSI module
    TSI_GENCS_EOSF_MASK; 						// writing one to clear the end of scan flag
}

/*******************************************************
 * @function	: function to scan for the values and return slider values
 *
 * @parameters	: none
 * @return		: slider scan value after offset calculation
 *******************************************************/

int TSI_scan()
{
    unsigned int scan = 0;
    TSI0->DATA =  TSI_DATA_TSICH(10u); 						//setting channel 10
    TSI0->DATA |= TSI_DATA_SWTS_MASK;		 				//software trigger to start the scan
        while (!(TSI0->GENCS & TSI_GENCS_EOSF_MASK )) 		// waiting for the scan to complete 32 times
          __asm volatile("NOP");
    scan = TOUCH_DATA - TOUCH_OFFSET;
#ifdef DEBUG
    //printf("\nSLIDER VALUE:%d\n", scan);
#endif
    TSI0->GENCS |= TSI_GENCS_EOSF_MASK ; 					//writing one to clear the end of scan flag
    return scan;
}

/***********************************************end*******************************************************************/
