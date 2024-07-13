#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define ARRSIZE 20

main(int argc, char **argv)
{
	int myid, size;
	int i, j, sum;
	int *A;
	int *A_sub;	
	int elements_per_process;
	int total_sum;	
	
	//Initialize MPI environment 
	MPI_Init(&argc,&argv);
	
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	//Exit the code if the number of processes is not equal to 4
	if(size!=4)
	{
		printf("\nNumber of processes should be 4! Exiting now!\n");
		MPI_Finalize();
		return;
	}
	
	elements_per_process = ARRSIZE/size;
	
	//If root allocate and initialize the arrays
	if(myid==0)
	{
		printf("\nElements per process = %d",elements_per_process);
		
		A = (int *)malloc(ARRSIZE*sizeof(int));
		
		//Initialize data to some value
		for(i=0;i<ARRSIZE;i++)
		{			
			A[i] = i;			
		}
		
		//print the data
		printf("\nInitial data: \n");
		for(i=0;i<ARRSIZE;i++)
		{
			printf("\t%d\n", A[i]);			
		}		
	}	
	
	//Allocate memory for temorary arrays
	A_sub = (int *)malloc(elements_per_process*sizeof(int));
	
	//Distribute / Scatter the data from root = 0
	MPI_Scatter(A, elements_per_process, MPI_INT, A_sub, elements_per_process, MPI_INT, 0, MPI_COMM_WORLD);
	
	sum = 0;
	//Every process adds sub arrays
	for(i=0;i<elements_per_process;i++)
	{
		sum = sum + A_sub[i];		
	}
	
	//Gather the data 
	MPI_Reduce(&sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	//If root
	if(myid==0)
	{
		//print the data
		printf("\ntotal sum = %d  \n", total_sum);
		printf("\nProgram exit!\n");
	
		//Free arrays
		free(A); 
	}
		
	//Free temporary allocated memory
	free(A_sub);
	
	//End MPI environment        
	MPI_Finalize();
}
