#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <test.h>
#include "cbfifo.h"
#include "pwm_LED.h"
#include "statemachine.h"
#include "sysclock.h"

extern test_flag;
/*************************************************
 * @function	: function to test cbfifo datatype other than str
 *************************************************/
int test_cbfifo()
{
int count=0;      //counter to keep track of the passed test cases
//***************************************************check enque operation*******************************************************************//
//test case to check if nbyte is 0
   cbfifo qt;
   cbfifo_init(&qt);
   int t1;
   long double a=310;

   t1=cbfifo_enqueue(&qt,&a, 0);
   if(t1==0)
    {
    //printf("test case passed 1");
    count = count + 1;
   }
   else
   {
    printf("throw error if nbyte is 0\n");
   }
//test case to check if buf is null
   int t2;
   long double b=23;
   t2=cbfifo_enqueue(&qt,NULL, sizeof(b));
   if(t2==-1)
    {
  // printf("test case passed");
   count = count + 1;
   }
   else
   {
    printf("throw error if buf is NULL\n");
   }
//test case to enque till bufferlength goes more than or equals capacity 128 and then throw error
   long double c=310,d=23,e=310,f=23,g=310,h=23,i=23,j=23,k=23,l=23,m=23,n=23,o=23;
   int t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15;
   t3=cbfifo_enqueue(&qt,&c, sizeof(c));
       //printf("c=%d\n",c);
      t4=cbfifo_enqueue(&qt,&d, sizeof(d));
      t5=cbfifo_enqueue(&qt,&e, sizeof(e));
       //printf("e=%d\n",e);
      t6=cbfifo_enqueue(&qt,&f, sizeof(f));
      t7=cbfifo_enqueue(&qt,&g, sizeof(g));
      t8=cbfifo_enqueue(&qt,&h, sizeof(h));
      t9=cbfifo_enqueue(&qt,&i, sizeof(i));
      t10=cbfifo_enqueue(&qt,&j, sizeof(j));
      t11=cbfifo_enqueue(&qt,&k, sizeof(k));
      t12=cbfifo_enqueue(&qt,&l, sizeof(l));
      t13=cbfifo_enqueue(&qt,&m, sizeof(m));
      t14=cbfifo_enqueue(&qt,&n, sizeof(n));
      t15=cbfifo_enqueue(&qt,&o, sizeof(o));
   if(t3!=0&&t4!=0&&t5!=0&&t6!=0&&t7!=0&&t8!=0&&t9!=0&&t10!=0&&t11!=0&&t12!=0&&t13!=0&&t14!=0&&t15!=0)
    {
    //printf("test cases passed1");
    count = count + 1;
   }
   else
   {
    printf("throw error as bufferlength goes more than or equals capacity 128\n");
    //count = count + 1;
   }

//***************************************************check deque operation*******************************************************************/
//test case to check if nbyte is 0

   int t16 = cbfifo_dequeue(&qt,&a, 0);
   if(t16!=0)
    {
    printf("test case passed2");
   }
   else
   {
   // printf("throw error if nbyte is 0\n");
    count = count + 1;
   }
   int t17,t18,t19,t20,t21,t22,t23,t24,t25,t26,t27,t28;
//test case to enque till bufferlength goes to zero
   t17=cbfifo_dequeue(&qt,&b, sizeof(b));
   t18=cbfifo_dequeue(&qt,&c, sizeof(c));
   t19=cbfifo_dequeue(&qt,&d, sizeof(d));
   t20=cbfifo_dequeue(&qt,&e, sizeof(e));
   t21=cbfifo_dequeue(&qt,&f, sizeof(f));
   t22=cbfifo_dequeue(&qt,&g, sizeof(g));
   t23=cbfifo_dequeue(&qt,&h, sizeof(h));
   t24=cbfifo_dequeue(&qt,&i, sizeof(i));
   t25=cbfifo_dequeue(&qt,&j, sizeof(j));
   t26=cbfifo_dequeue(&qt,&k, sizeof(k));
   t27=cbfifo_dequeue(&qt,&l, sizeof(l));
   t28=cbfifo_dequeue(&qt,&o, sizeof(o));

   if(t17!=0&&t18!=0&&t19!=0&&t20!=0&&t21!=0&&t22!=0&&t23!=0&&t24!=0&&t25!=0&&t26!=0&&t27!=0&&t28!=0){
    //printf("test cases passed3");
    count = count + 1;
   }
   else
    {
    printf("throw error as bufferlength goes more than or equals capacity 256\n");
   //count = count + 1;
   }
//****************test case to enque full and deque full and enque and deque again************************************************************/
   int t30;
   long double p=23;
   t30=cbfifo_enqueue(&qt,&p, sizeof(p));
   if(t30!=0)
    {
    //printf("test case passed");
    count = count + 1;
   }
   else
   {
    printf("throw error");
   }
   int t31;
   t31=cbfifo_dequeue(&qt,&p, sizeof(p));
   if(t31!=0)
   {
  //  printf("test case passed");
    count = count + 1;
   }
   else
   {
    printf("throw error\n");
   }
   printf("\nTotal Test conditions passed for long double data type: %d \r\n", count);
   test_flag = 1;
   return 0;

}


cbfifo txb;				//transmit buffer
cbfifo rxb;             //receive buffer

/*************************************************
 * @function	: function to test cbfifo
 *
 * @parameters	: none
 * @return		: 1 on success 0 on failure
 *************************************************/

bool test_cbfifo_str()
{
	char *str ="To be, or not to be: that is the question:\n"
    "Whether 'tis nobler in the mind to suffer\n"
    "The slings and arrows of outrageous fortune,\n"
    "Or to take arms against a sea of troubles,\n"
    "And by opposing end them? To die, to sleep--\n"
    "No more--and by a sleep to say we end\n"
    "The heart-ache and the thousand natural shocks\n"
    "That flesh is heir to, 'tis a consummation\n"
    "Devoutly to be wish'd. To die, to sleep;\n"
    "To sleep: perchance to dream: ay, there's the rub;\n"
    "For in that sleep of death what dreams may come\n"
    "When we have shuffled off this mortal coil,\n"
    "Must give us pause.";

  char buf[1024];                                        //transmit buffer
  char buf1[1024];                                       //receiver buffer
  const int cap = cbfifo_capacity();

/***************************************validate test****************************************************/
  assert(strlen(str) >= cap*2);
  assert(sizeof(buf) > cap);

  assert(strlen(str) >= cap*2);
  assert(sizeof(buf1) > cap);


/***************************************write zero bytes***********************************************/
  assert(cbfifo_enqueue(&txb,str, 0) == 0);
  assert(cbfifo_length(&txb) == 0);

  assert(cbfifo_length(&txb) == 0);
  assert(cbfifo_dequeue(&txb,buf, cap) == 0);
  assert(cbfifo_dequeue(&txb,buf, 1) == 0);

  assert(cbfifo_enqueue(&rxb,str, 0) == 0);
  assert(cbfifo_length(&rxb) == 0);

  assert(cbfifo_length(&rxb) == 0);
  assert(cbfifo_dequeue(&rxb,buf1, cap) == 0);
  assert(cbfifo_dequeue(&rxb,buf1, 1) == 0);

/****************************************checking transmit buffer****************************************/

/****************************Enqueue 30 bytes;  Dequeue 10, then another 30*****************************/
  assert(cbfifo_enqueue(&txb,str, 30) == 30);
  assert(cbfifo_length(&txb) == 30);
  assert(cbfifo_dequeue(&txb,buf, 10) == 10);
  assert(cbfifo_length(&txb) == 20);
  assert(cbfifo_dequeue(&txb,buf+10, 30) == 20);
  assert(cbfifo_length(&txb) == 0);
  assert(strncmp(buf, str, 30) == 0);

/**********************************Enqueue 30 bytes, then Dequeue same amt*******************************/
  assert(cbfifo_enqueue(&txb,str, 30) == 30);
  assert(cbfifo_length(&txb) == 30);
  assert(cbfifo_dequeue(&txb, buf, 30) == 30);
  assert(strncmp(buf, str, 30) == 0);
  assert(cbfifo_length(&txb) == 0);

/****************************** Add 20 bytes and pull out 18*******************************************/
  assert(cbfifo_enqueue(&txb,str, 20) == 20);
  assert(cbfifo_length(&txb) == 20);
  assert(cbfifo_dequeue(&txb,buf, 18) == 18);
  assert(cbfifo_length(&txb) == 2);
  assert(strncmp(buf, str, 18) == 0);

/***************************** Now add a bunch of data in 4 chunks************************************/
  int chunk_size = (cap-2) / 4;
  for (int i=0; i<4; i++)
  {
    assert(cbfifo_enqueue(&txb,str+i*chunk_size, chunk_size) == chunk_size);
    assert(cbfifo_length(&txb) == (i+1)*chunk_size + 2);
  }
  assert(cbfifo_length(&txb) == 4*chunk_size + 2);

/****************************** Take out the 2 remaining bytes from above***********************************/
  assert(cbfifo_dequeue(&txb,buf, 2) == 2);
  assert(strncmp(buf, str+18, 2) == 0);

/****************************** now read those chunks out a byte at a time*********************************/
  for (int i=0; i<chunk_size*4; i++)
  {
    assert(cbfifo_dequeue(&txb,buf+i, 1) == 1);
    assert(cbfifo_length(&txb) == chunk_size*4 - i - 1);
  }
  assert(strncmp(buf, str, chunk_size*4) == 0);

/*************************************  Enqueue when read < write:*******************************************
*1.   bytes < CAP-write  (1)
 2.   bytes exactly CAP-write  (2)
 3.   bytes > CAP-write but < space available (3)
 4.   bytes exactly the space available (4)
 5.   bytes > space available (5)
***********************************************************************************************************/
  assert(cbfifo_enqueue(&txb,str, 32) == 32);
  assert(cbfifo_length(&txb) == 32);
  assert(cbfifo_dequeue(&txb,buf, 16) == 16);
  assert(cbfifo_length(&txb) == 16);
  assert(strncmp(buf, str, 16) == 0);

  assert(cbfifo_enqueue(&txb,str+32, 32) == 32);  // (1)
  assert(cbfifo_length(&txb) == 48);
  assert(cbfifo_enqueue(&txb,str+64, cap-64) == cap-64);  // (2)
  assert(cbfifo_length(&txb) == cap-16);
  assert(cbfifo_dequeue(&txb,buf+16, cap-16) == cap-16);
  assert(strncmp(buf, str, cap) == 0);

  assert(cbfifo_enqueue(&txb,str, 32) == 32);  // advance so that read < write
  assert(cbfifo_length(&txb) == 32);
  assert(cbfifo_dequeue(&txb,buf, 16) == 16);
  assert(cbfifo_length(&txb) == 16);
  assert(strncmp(buf, str, 16) == 0);

  assert(cbfifo_enqueue(&txb,str+32, cap-20) == cap-20);  // (3)
  assert(cbfifo_length(&txb) == cap-4);
  assert(cbfifo_dequeue(&txb,buf, cap-8) == cap-8);
  assert(strncmp(buf, str+16, cap-8) == 0);
  assert(cbfifo_length(&txb) == 4);
  assert(cbfifo_dequeue(&txb,buf, 8) == 4);
  assert(strncmp(buf, str+16+cap-8, 4) == 0);
  assert(cbfifo_length(&txb) == 0);

  assert(cbfifo_enqueue(&txb,str, 49) == 49);  // advance so that read < write
  assert(cbfifo_length(&txb) == 49);
  assert(cbfifo_dequeue(&txb,buf, 16) == 16);
  assert(cbfifo_length(&txb) == 33);
  assert(strncmp(buf, str, 16) == 0);

/*********************************************Checking Receive Buffer*********************************************/

/***************************************write zero bytes***********************************************/
  assert(cbfifo_length(&rxb) == 0);
  assert(cbfifo_dequeue(&rxb,buf1, cap) == 0);
  assert(cbfifo_dequeue(&rxb,buf1, 1) == 0);

/****************************Enqueue 30 bytes;  Dequeue 10, then another 30*****************************/
  assert(cbfifo_enqueue(&rxb,str, 30) == 30);
  assert(cbfifo_length(&rxb) == 30);
  assert(cbfifo_dequeue(&rxb,buf1, 10) == 10);
  assert(cbfifo_length(&rxb) == 20);
  assert(cbfifo_dequeue(&rxb,buf1+10, 30) == 20);
  assert(cbfifo_length(&rxb) == 0);
  assert(strncmp(buf1, str, 30) == 0);

/**********************************Enqueue 30 bytes, then Dequeue same amt*******************************/
  assert(cbfifo_enqueue(&rxb,str, 30) == 30);
  assert(cbfifo_length(&rxb) == 30);
  assert(cbfifo_dequeue(&rxb, buf1, 30) == 30);
  assert(strncmp(buf1, str, 30) == 0);
  assert(cbfifo_length(&rxb) == 0);

/****************************** Add 20 bytes and pull out 18*******************************************/
  assert(cbfifo_enqueue(&rxb,str, 20) == 20);
  assert(cbfifo_length(&rxb) == 20);
  assert(cbfifo_dequeue(&rxb,buf1, 18) == 18);
  assert(cbfifo_length(&rxb) == 2);
  assert(strncmp(buf1, str, 18) == 0);

/***************************** Now add a bunch of data in 4 chunks************************************/
  chunk_size = (cap-2) / 4;
  for (int i=0; i<4; i++)
  {
    assert(cbfifo_enqueue(&rxb,str+i*chunk_size, chunk_size) == chunk_size);
    assert(cbfifo_length(&rxb) == (i+1)*chunk_size + 2);
  }
  assert(cbfifo_length(&rxb) == 4*chunk_size + 2);

/****************************** Take out the 2 remaining bytes from above***********************************/
  assert(cbfifo_dequeue(&rxb,buf1, 2) == 2);
  assert(strncmp(buf1, str+18, 2) == 0);

/****************************** now read those chunks out a byte at a time*********************************/
  for (int i=0; i<chunk_size*4; i++) {
    assert(cbfifo_dequeue(&rxb,buf1+i, 1) == 1);
    assert(cbfifo_length(&rxb) == chunk_size*4 - i - 1);
  }
  assert(strncmp(buf1, str, chunk_size*4) == 0);

/*************************************  Enqueue when read < write:*******************************************
  *1.   bytes < CAP-write  (1)
   2.   bytes exactly CAP-write  (2)
   3.   bytes > CAP-write but < space available (3)
   4.   bytes exactly the space available (4)
   5.   bytes > space available (5)
***********************************************************************************************************/
  assert(cbfifo_enqueue(&rxb,str, 32) == 32);  // advance so that read < write
  assert(cbfifo_length(&rxb) == 32);
  assert(cbfifo_dequeue(&rxb,buf1, 16) == 16);
  assert(cbfifo_length(&rxb) == 16);
  assert(strncmp(buf1, str, 16) == 0);

  assert(cbfifo_enqueue(&rxb,str+32, 32) == 32);  // (1)
  assert(cbfifo_length(&rxb) == 48);
  assert(cbfifo_enqueue(&rxb,str+64, cap-64) == cap-64);  // (2)
  assert(cbfifo_length(&rxb) == cap-16);
  assert(cbfifo_dequeue(&rxb,buf1+16, cap-16) == cap-16);
  assert(strncmp(buf1, str, cap) == 0);

  assert(cbfifo_enqueue(&rxb,str, 32) == 32);  // advance so that read < write
  assert(cbfifo_length(&rxb) == 32);
  assert(cbfifo_dequeue(&rxb,buf1, 16) == 16);
  assert(cbfifo_length(&rxb) == 16);
  assert(strncmp(buf1, str, 16) == 0);

  assert(cbfifo_enqueue(&rxb,str+32, cap-20) == cap-20);  // (3)
  assert(cbfifo_length(&rxb) == cap-4);
  assert(cbfifo_dequeue(&rxb,buf1, cap-8) == cap-8);
  assert(strncmp(buf1, str+16, cap-8) == 0);
  assert(cbfifo_length(&rxb) == 4);
  assert(cbfifo_dequeue(&rxb,buf1, 8) == 4);
  assert(strncmp(buf1, str+16+cap-8, 4) == 0);
  assert(cbfifo_length(&rxb) == 0);

  assert(cbfifo_enqueue(&rxb,str, 49) == 49);  // advance so that read < write
  assert(cbfifo_length(&rxb) == 49);
  assert(cbfifo_dequeue(&rxb,buf1, 16) == 16);
  assert(cbfifo_length(&rxb) == 33);
  assert(strncmp(buf1, str, 16) == 0);

  printf("Passed all the test cases for CBFIFO\n\r");
  test_flag = 2;
  return 1;
}

void test_leds()
{
    set_led_colour(1,0,0);
    delay(500);
    set_led_off(true);
    delay(100);

    set_led_colour(0,0,1);
    delay(500);
    set_led_off(true);
    delay(100);

    set_led_colour(0,1,0);
    delay(500);
    set_led_off(true);
    delay(100);

    printf("Tested LEDs\n\n\n\r");
    test_flag = 3;
}
