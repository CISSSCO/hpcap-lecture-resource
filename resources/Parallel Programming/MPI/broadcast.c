#include"stdio.h"
#include"mpi.h"

int main(int argc, char **argv)
{
	int myid, size;
	int data;
	
	//Initialize MPI environment 
	MPI_Init(&argc,&argv);
	
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	//Initialize data to some value
	data = 20;
	
	//If root
	if(myid==0)
	{
		data = 10;			
	}
	//Bradcast the data
	MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	//Every process prints the value of data
	printf("myid:%d \t data = %d\n",myid, data);
	
	//End MPI environment        
	MPI_Finalize();
}
