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


pthread_mutex_t mutex;
int sum;
/* Global variable:  accessible to all threads */
int thread_count;  

void *Hello(void* rank);  /* Thread function */

/*--------------------------------------------------------------------*/
int main() {
   long       thread;  /* Use long in case of a 64-bit system */
   pthread_t* thread_handles; 

   /* Get number of threads from command line */
   thread_count = 64; 
   sum = 0;
   thread_handles = malloc (thread_count*sizeof(pthread_t)); 
   pthread_mutex_init(&mutex, NULL);
    
   for (thread = 0; thread < thread_count; thread++)  
      pthread_create(&thread_handles[thread], NULL,
          Hello, (void*) thread);  

   //printf("Hello from the main thread\n");

   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL); 

    printf("\n sum = %d",sum);

   pthread_mutex_destroy(&mutex);
   free(thread_handles);
   return 0;
}  /* main */

/*-------------------------------------------------------------------*/
void *Hello(void* rank) {
   long my_rank = (long) rank;  /* Use long in case of 64-bit system */ 
    
   pthread_mutex_lock(&mutex);
   sum += my_rank;
   pthread_mutex_unlock(&mutex);
   
   //printf("Hello from thread %ld of %d\n", my_rank, thread_count);

   return NULL;
}  /* Hello */

