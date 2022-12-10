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

#ifndef _CBFIFO_H_
#define _CBFIFO_H_

#include <stdlib.h>  // for size_t
#include <stdbool.h>


#define CAPACITY 256
// Declare memory for the fifo, and the write and read pointers
typedef struct
{
uint8_t  my_queue[CAPACITY];                             // the queue
uint8_t   wptr;                                          // write pointer
uint8_t   rptr;                                          // read pointer
//bool full_queue;
int bufferlength;				//declare bufferlength to keep track of the data in use.initializing bufferlength as 0
} cbfifo;

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
size_t cbfifo_enqueue(cbfifo * data,void *buf, size_t nbyte);


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
 *
 * To further explain the behavior: If the FIFO's current length is 24
 * bytes, and the caller requests 30 bytes, cbfifo_dequeue should
 * return the 24 bytes it has, and the new FIFO length will be 0. If
 * the FIFO is empty (current length is 0 bytes), a request to dequeue
 * any number of bytes will result in a return of 0 from
 * cbfifo_dequeue.
 ***********************************************************************/
size_t cbfifo_dequeue(cbfifo * data,void *buf, size_t nbyte);

/*****************************************************************
 * Returns the FIFO's capacity
 *
 * Parameters:
 *   none
 *
 * Returns:
 *   The capacity, in bytes, for the FIFO
 ******************************************************************/
size_t cbfifo_capacity();
/******************************************************************
 * @function	: function to initialize cbfifo
 *
 * @parameters	: data
 * @return		: none
 ******************************************************************/
void cbfifo_init(cbfifo * data);
/*************************************************
 * @function	: function to check if cbfifo is empty
 *
 * @parameters	: data
 * @return		: bufferlength
 ******************************************************************/
bool cbfifo_empty(cbfifo * data);
/********************************************************************
 * @function	: function to check if cbfifo is full
 *
 * @parameters	: data
 * @return		: CAPACITY
 ******************************************************************/
bool cbfifo_full(cbfifo * data);
/******************************************************************
 * @function	: function returns cbfifo length
 *
 * @parameters	: data
 * @return		: cbfifo length
 ******************************************************************/
size_t cbfifo_length(cbfifo * data);
/*********************************************end*******************************************************************/
#endif // _CBFIFO_H_

