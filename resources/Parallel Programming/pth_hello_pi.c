/* File:  
 *    pth_hello.c
 *
 * Purpose:
 *    Illustrate basic use of pthreads:  create some threads,
 *    each of which prints a message.
 *
 * Input:
 *    none
 * Output:
 *    message from each thread
 *
 * Compile:  gcc -g -Wall -o pth_hello pth_hello.c -lpthread
 * Usage:    ./pth_hello <thread_count>
 *
 * IPP:   Section 4.2 (p. 153 and ff.)
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <math.h> 

#define N 99999
const int MAX_THREADS = 64;

/* Global variable:  accessible to all threads */
int thread_count;  
int global_flag;
double total_area;

void *Hello(void* rank);  /* Thread function */

/*--------------------------------------------------------------------*/
int main() {
   long       thread;  /* Use long in case of a 64-bit system */
   pthread_t* thread_handles; 
   double pi;

   /* Get number of threads from command line */
   thread_count = 10; 
   thread_handles = malloc (thread_count*sizeof(pthread_t)); 

    total_area = 0.0;
    global_flag = 0;

   for (thread = 0; thread < thread_count; thread++)  
      pthread_create(&thread_handles[thread], NULL,
          Hello, (void*) thread);  

   printf("Hello from the main thread\n");

   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL); 

    pi = 4.0*total_area;
	printf("\n Value of pi is = %.16lf\n", pi);

   free(thread_handles);
   return 0;
}  /* main */

/*-------------------------------------------------------------------*/
void *Hello(void* rank) {
   long my_rank = (long) rank;  /* Use long in case of 64-bit system */ 
    
    int i, start, end;
    double x, dx, area, y; 
    
    start = my_rank * (N/thread_count);
    end = start + (N/thread_count);

    if(my_rank == (thread_count-1))
    {
        end = N;
    }

    dx = 1.0/N;
	x = 0.0;
	area = 0.0;
	
	for(i=start;i<end;i++)
	{
		x = i*dx;
		y = sqrt(1-x*x);
		area += y*dx;
	}

    while(global_flag != my_rank);
    total_area = total_area + area;
    global_flag++;
    
   return NULL;
}  /* Hello */

