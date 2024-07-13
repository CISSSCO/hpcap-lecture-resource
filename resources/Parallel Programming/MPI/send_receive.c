#include"stdio.h"
#include"mpi.h"

int main(int argc, char **argv)
{
	int myid, size;
	int data_arr[2];
	MPI_Status status;
	
	//Initialize MPI environment 
	MPI_Init(&argc,&argv);
	
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	//Get my unique ID among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	// Process with ID exactly equal to 0
	if(myid==0)
	{
		//Initialize data to be sent
		data_arr[0] = 159;
		data_arr[1] = 357;
		
		//Print the data to be sent
		printf("\nmyid: %d \t data_arr[0] = %d", myid, data_arr[0]);
		printf("\nmyid: %d \t data_arr[1] = %d", myid, data_arr[1]);
		
		//Send data
		MPI_Send(data_arr, 2, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("\nmyid: %d \t Data sent.\n", myid);	
	}
	else if(myid==1)	// Process with ID exactly equal to 1
	{
		//Initialize receive array to some other data
		data_arr[0] = 10;
		data_arr[1] = 20;
		
		MPI_Recv(data_arr, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		
		printf("\nmyid: %d \t Data received.", myid);
		
		//Print received data
		printf("\nmyid: %d \t data_arr[0] = %d", myid, data_arr[0]);
		printf("\nmyid: %d \t data_arr[1] = %d", myid, data_arr[1]);
		
		printf("\n\nProgram exit!\n");	
	}
	
	//End MPI environment        
	MPI_Finalize();
}
