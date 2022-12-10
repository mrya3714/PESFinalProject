#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include "test_cbfifo.h"
#include "cbfifo.h"

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
   printf("Total Test conditions passed: %d \r\n", count);



   return 0;

}
