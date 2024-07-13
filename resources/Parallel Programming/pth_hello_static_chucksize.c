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

const int MAX_THREADS = 64;
const int NUM_ITER = 17;
const int chunksize = 3;

/* Global variable:  accessible to all threads */
int thread_count;  

void *Hello(void* rank);  /* Thread function */

/*--------------------------------------------------------------------*/
int main() {
   long       thread;  /* Use long in case of a 64-bit system */
   pthread_t* thread_handles; 

   /* Get number of threads from command line */
   thread_count = 3; 
   thread_handles = malloc (thread_count*sizeof(pthread_t)); 

   for (thread = 0; thread < thread_count; thread++)  
      pthread_create(&thread_handles[thread], NULL,
          Hello, (void*) thread);  

   //printf("Hello from the main thread\n");

   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL); 

   free(thread_handles);
   return 0;
}  /* main */

/*-------------------------------------------------------------------*/
void *Hello(void* rank) {
   long my_rank = (long) rank;  /* Use long in case of 64-bit system */ 
    int i,j;
    int start, end;
    
    start = my_rank * chunksize;
    
   //printf("Hello from thread %ld of %d\n", my_rank, thread_count);
    for(i=start;i<NUM_ITER;i+=(chunksize*thread_count))
    {
        end = i+chunksize;
        if(end >= NUM_ITER)
        { 
            end = NUM_ITER;
        }
        for(j=i;j<end;j++)
        {   
            printf("\n Thread number %ld : processing %d ", my_rank, j);
        }
    }
   return NULL;
}  /* Hello */











/*


    for(i=0;i<10;i++)
    {
        printf("\n Thread number %d : processing %d ", my_rank, i);
    }


Thread number 0 : processing 0
Thread number 0 : processing 1
Thread number 0 : processing 2
Thread number 0 : processing 3
Thread number 0 : processing 4
Thread number 1 : processing 5
Thread number 1 : processing 6
Thread number 1 : processing 7
Thread number 1 : processing 8
Thread number 1 : processing 9
*/



