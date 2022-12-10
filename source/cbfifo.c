/*******************************************************************************************************************
 * Author: Mrunal Y
 * References:Lalit Pandit's lecture slides, Dean ch8,
 “ARM®v6-M Architecture Reference Manual”,Alexander, Dean.
  Embedded Systems Fundamentals with ARM Cortex-M Based Microcontrollers : A Practical Approach

 *
 *PREVIOUS CBFIFO code modified for better understanding and handling the buffer transmitter receiver operations easily
 *
 * Credits for code :  https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8/Serial-Demo
 *
 * @Credits for concepts and crafting: Lalit Pandit
 *
 * Description : contains 7 functions to create cbfifo, enqueue and dequeue the data, check if buffer is full or
 * empty
 ******************************************************************************************************************/

/*************************************headers and preprocessor directive********************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cbfifo.h"
#include <stdbool.h>
#include "UART.h"
#include "MKL25Z4.h"

/******************************************************************
 * @function	: function to initialize cbfifo
 *
 * @parameters	: data
 * @return		: none
 ******************************************************************/

void cbfifo_init(cbfifo * data)
{
unsigned int i;
  for (i=0; i<CAPACITY; i++)
  {
   data->my_queue[i]='_';
  }
data->wptr = 0;        // write pointer
data->rptr = 0;        // read pointer
data->bufferlength=0;  //declare bufferlength to keep track of the data in use.initializing bufferlength as 0
}

/*******************************************************************
 * @function	: function to check if cbfifo is empty
 *
 * @parameters	: data
 * @return		: bufferlength 0
 ******************************************************************/
bool cbfifo_empty(cbfifo * data)
{
  return data->bufferlength == 0;
}

/********************************************************************
 * @function	: function to check if cbfifo is full
 *
 * @parameters	: data
 * @return		: CAPACITY
 * *******************************************************************/
bool cbfifo_full(cbfifo * data)
{
  return data->bufferlength == CAPACITY;
}

/******************************************************************
 * @function	: function returns cbfifo length,to keep the track of the buffer length
 *
 * @parameters	: data
 * @return		: cbfifo length
 ******************************************************************/
size_t cbfifo_length(cbfifo * data)
{
  return data->bufferlength;
}

/*************************fuction to increment pointer***************/
static uint8_t nextPtr(uint8_t ptr) {
if(ptr==CAPACITY-1){       		                            //CAPACITY-1 because indexing starts from 0
    return 0;
}
else{
    return ptr+1;                                       //increment ptr
}
} // nextPtr()

/******************************************************************
 * Enqueues data onto the FIFO, up to the limit of the available FIFO
 * capacity.
 *
 * Parameters:
 *   buf      Pointer to the data
 *   nbyte    Max number of bytes to enqueue
 *
 * Returns:
 *   The number of bytes actually enqueued, which could be 0. In case
 * of an error, returns (size_t) -1.
 ********************************************************************/

size_t cbfifo_enqueue(cbfifo * data,void *buf, size_t nbyte)
{
/*condition to handle bufferlength greater than or equal to capacity*/
 if((data->bufferlength)>=CAPACITY)
 {
     return -1;
 }
 /*if nbyte is greater than (CAPACITY-bufferlength) then equal*/
 if(nbyte>=(CAPACITY-(data->bufferlength)))
 {
    nbyte=CAPACITY-(data->bufferlength);
 }
 /*return 0 if nbyte is 0*/
 if(nbyte==0)
 {
    return 0;
 }
 /*if there is no data then return -1*/
 if(buf==NULL)
 {
    return -1;
 }
 /*Enque data*/
 __disable_irq();                                      //deisable interrupt
 int j=0;
 uint8_t temp_data[nbyte];                             //array declaration to store buf data
 memcpy(temp_data,buf,nbyte);                          //copy the data from buf to the array
 //printf("Buf: %d\n",(*(int*)buf) );
 if((data->bufferlength)!=CAPACITY)
{
 for(j=0;j<nbyte;j++)
    {
    data->my_queue[data->wptr]=temp_data[j];
    //printf("Data in data:%d\n ", temp_data[j]);
    //printf("Data in my_queue:%d\n ", data->my_queue[data->wptr]);
    uint8_t count1 = 0;
    count1 = nextPtr(data->wptr);                        //increment wptr
    data->wptr=count1;
    data->bufferlength++;                                //increment bufferlength
    if((data->wptr) == CAPACITY)
    {
        data->wptr=0;
    }
    }
 }
 //printf("Bufferlength%d\n",data->bufferlength);
// printf("j=%d\n",j);
 __enable_irq();
 return nbyte;
}


/********************************************************************
 * Attempts to remove ("dequeue") up to nbyte bytes of data from the
 * FIFO. Removed data will be copied into the buffer pointed to by buf.
 *
 * Parameters:
 *   buf      Destination for the dequeued data
 *   nbyte    Bytes of data requested
 *
 * Returns:
 *   The number of bytes actually copied, which will be between 0 and
 *   nbyte.
 ***********************************************************************/

size_t cbfifo_dequeue(cbfifo * data,void *buf, size_t nbyte){
	int i =0;
      /*return 0 if bufferlength is 0*/
    if((data->bufferlength)<=0)//<
    {
     return 0;
    }
    /*return 0 if bufferlength is greater than the capacity*/
    if((data->bufferlength)>CAPACITY)
    {
     return 0;
    }
     /*return 0 if nbyte is 0*/
    if(nbyte==0)
    {
    return 0;
    }
     /*if there is no data then return -1*/
    if(buf==NULL)
    {
    return -1;
    }
    /*if nbyte>bufferlength equal them*/
    if(nbyte>(data->bufferlength))
    {
    nbyte=(data->bufferlength);
    }
    /*deque data*/
//printf("Buf deque: %d\n",(*(int*)buf) );
    __disable_irq();
uint8_t temp_data[nbyte];
if((data->bufferlength)!=0)
{
    for(i=0;i<nbyte;i++)
    {
    //printf("Data in data deque:%d\n ", temp_data[i]);
    //printf("Data in my_queue deque:%d\n ", data->my_queue[data->wptr]);
    temp_data[i]=data->my_queue[data->rptr];
    uint8_t count2 = nextPtr(data->rptr);  				//decrement rptr
    data->rptr = count2;
    data->bufferlength--;
    if((data->rptr) == CAPACITY)
    {
        data->rptr = 0;
    }
    }
    memcpy(buf,temp_data,nbyte);
}
//printf("Bufferlength deque%d\n",data->bufferlength);
//printf("i=%d\n",i);

__enable_irq();
return nbyte;
}

/*****************************************************************
 * Returns the FIFO's capacity
 *
 * Parameters:
 *   none
 *
 * Returns:
 *   The capacity, in bytes, for the FIFO
 ******************************************************************/
size_t cbfifo_capacity()
{
return (size_t)CAPACITY;
}

/*********************************************end*******************************************************************/





