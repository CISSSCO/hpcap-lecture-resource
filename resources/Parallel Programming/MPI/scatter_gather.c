#include"stdio.h"
#include"mpi.h"
#include<stdlib.h>

#define ARRSIZE 20

int main(int argc, char **argv)
{
	int myid, size;
	int i;
	int data[ARRSIZE];
	int receive_data[ARRSIZE/4];	
	
	//Initialize MPI environment 
	MPI_Init(&argc,&argv);
	
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	//Exit the code if the number of processes is not equal to 4
	if(size!=4)
	{
		printf("\n Please use EXACTLY 4 processes!\n");
		MPI_Finalize();
		exit(0);
	}
	
	//If root
	if(myid==0)
	{
		//Initialize data to some value
		for(i=0;i<ARRSIZE;i++)
		{
			data[i] = i;			
		}
		
		//print the data
		printf("\nInitial data: ");
		for(i=0;i<ARRSIZE;i++)
		{
			printf("\t%d", data[i]);			
		}
	}
	//Distribute / Scatter the data from root = 0
	MPI_Scatter(&data, ARRSIZE/4, MPI_INT, &receive_data, ARRSIZE/4, MPI_INT, 0, MPI_COMM_WORLD);
	
	//Every process works on ARRSIZE/4 of data
	for(i=0;i<ARRSIZE/4;i++)
	{
		// Multiply received data by two
		receive_data[i] = receive_data[i]*2;				
	}
	
	//Collect / Gather the data at root = 0 
	MPI_Gather(&receive_data, ARRSIZE/4, MPI_INT, &data, ARRSIZE/4, MPI_INT, 0, MPI_COMM_WORLD);
	
	//If root
	if(myid==0)
	{
		//print the data
		printf("\nFinal data: ");
		for(i=0;i<ARRSIZE;i++)
		{
			printf("\t%d", data[i]);			
		}
		printf("\n\nProgram exit!\n");
	}
	
	//End MPI environment        
	MPI_Finalize();
}
