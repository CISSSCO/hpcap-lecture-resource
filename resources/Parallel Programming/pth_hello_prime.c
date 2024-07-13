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

#define N 10000
const int MAX_THREADS = 64;

/* Global variable:  accessible to all threads */
int thread_count;  
int global_flag;
int total_count;

void *Hello(void* rank);  /* Thread function */

/*--------------------------------------------------------------------*/
int main() {
   long       thread;  /* Use long in case of a 64-bit system */
   pthread_t* thread_handles; 

   /* Get number of threads from command line */
   thread_count = 10; 
   thread_handles = malloc (thread_count*sizeof(pthread_t)); 

    total_count = 1;
    global_flag = 0;

   for (thread = 0; thread < thread_count; thread++)  
      pthread_create(&thread_handles[thread], NULL,
          Hello, (void*) thread);  

   printf("Hello from the main thread\n");

   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL); 

    printf("\n total_count = %d\n", total_count);

   free(thread_handles);
   return 0;
}  /* main */

/*-------------------------------------------------------------------*/
void *Hello(void* rank) {
   long my_rank = (long) rank;  /* Use long in case of 64-bit system */ 
    
    int i, j, count, flag, start, end;

    count = 0;
    start = my_rank * (N/thread_count);
    end = start + (N/thread_count);

    if (my_rank == 0)
    {
        start = 3;
    }
    if(my_rank == (thread_count-1))
    {
        end = N;
    }

    for(i=start;i<end;i++)
	{
	 	flag = 0;
		for(j=2;j<i;j++)	
	    {
		    if((i%j) == 0)
		    {
			    flag = 1;
			    break;
		    }
	    }
        if(flag == 0)
        {
        	count++;
        }
	}

    while(global_flag != my_rank);
    total_count = total_count + count;
    global_flag++;
    
   return NULL;
}  /* Hello */

