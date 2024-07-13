#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#define VECTORSIZE 10000

int main(int argc, char **argv)
{
	int myid, size;
	int i, j, k, sum;
	int *A, *B, *C;		
	double exe_time;
	struct timeval stop_time, start_time;
	
	//Allocate and initialize the arrays
	A = (int *)malloc(VECTORSIZE*VECTORSIZE*sizeof(int));
	B = (int *)malloc(VECTORSIZE*VECTORSIZE*sizeof(int));
	C = (int *)malloc(VECTORSIZE*VECTORSIZE*sizeof(int));
	
	//Initialize data to some value
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			A[i*VECTORSIZE+j] = 1;
			B[i*VECTORSIZE+j] = 2;
			C[i*VECTORSIZE+j] = 0;	
		}
	}
	
	//print the data
	/*printf("\nInitial data: \n");
	printf("\n A matrix:\n");
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			printf("\t%d ", A[i*VECTORSIZE+j]);	
		}
		printf("\n");
	}
	printf("\n B matrix:\n");
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			printf("\t%d ", B[i*VECTORSIZE+j]);	
		}
		printf("\n");
	}	*/
	
	gettimeofday(&start_time, NULL);
	
	#pragma acc parallel loop gang vector
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			sum = 0;
			for(k=0;k<VECTORSIZE;k++)
			{
				sum = sum + A[i*VECTORSIZE+k]*B[k*VECTORSIZE+j];	
			}
			C[i*VECTORSIZE+j] =  sum;
		}
	}
	
	gettimeofday(&stop_time, NULL);	
	exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));
	
	//print the data
	/*printf("\n C matrix:\n");
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			printf("\t%d ", C[i*VECTORSIZE+j]);	
		}
		printf("\n");
	}*/
	printf("\n Execution time is = %lf seconds\n", exe_time);
	
	printf("\nProgram exit!\n");
	
	//Free arrays
	free(A); 
	free(B);
	free(C);
}
