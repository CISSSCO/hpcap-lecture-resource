#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define ARRSIZE 200

/*
    export PGI_ACC_NOTIFY=1
    pgcc -Minfo=accel -ta=tesla:managed vector_addition_v1.c
    pgcc -Minfo=accel -ta=multicore vector_addition_v1.c
*/

int main(int argc, char **argv)
{
	int i;
	//int *restrict A, *restrict B, *restrict C;
	int *A, *B, *C;	
	
	//Allocate and initialize the arrays
	A = (int *)malloc(ARRSIZE*sizeof(int));
	B = (int *)malloc(ARRSIZE*sizeof(int));
	C = (int *)malloc(ARRSIZE*sizeof(int));
	
	//Initialize data to some value
	for(i=0;i<ARRSIZE;i++)
	{
		A[i] = i;
		B[i] = i;
	}
	
	//print the data
	printf("\nInitial data: \n");
	for(i=0;i<ARRSIZE;i++)
	{
		printf("\t%d %d\t", A[i], B[i]);
	}	
	
	// Perform operations in parallel
	#pragma acc kernels 
	for(i=0;i<ARRSIZE;i++)
	{
		C[i] = A[i] + B[i];
	}
	
	//print the data
	printf("\nVector addition output: \n");
	for(i=0;i<ARRSIZE;i++)
	{
		printf("\t%d ", C[i]);	
	}
	printf("\nProgram exit!\n");
	
	//Free arrays
	free(A); 
	free(B);
	free(C);
}
