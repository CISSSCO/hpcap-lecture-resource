#include"stdio.h"
#include"mpi.h"

int main(int argc, char **argv)
{
	int myid, size;
	int data_arr[2], data_arr2[2];
	MPI_Status status;
	MPI_Request request;
	
	//Initialize MPI environment 
	MPI_Init(&argc,&argv);
	
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	//If root
	if(myid==0)
	{
		//Initialize data to be sent
		data_arr[0] = 205;
		data_arr[1] = 408;
		
		data_arr2[0] = 11;
		data_arr2[1] = 12;
		
		//Print the data to be sent
		printf("\nmyid: %d \t data_arr[0] = %d", myid, data_arr[0]);
		printf("\nmyid: %d \t data_arr[1] = %d", myid, data_arr[1]);
		
		//Send data
		
		MPI_Irecv(data_arr2, 2, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
		sleep(15);
		MPI_Send(data_arr, 2, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Wait(&request,MPI_STATUS_IGNORE);
		printf("\nmyid: %d \t data_arr2[0] = %d", myid, data_arr2[0]);
		printf("\nmyid: %d \t data_arr2[1] = %d", myid, data_arr2[1]);
		printf("\nData sent.\n");	
	}
	if(myid==1)	// Process with id exactly equal to 1
	{
		//Initialize receive array to some other data
		data_arr[0] = 10;
		data_arr[1] = 20;
		
		data_arr2[0] = 1050;
		data_arr2[1] = 2050;
		
	    printf("\nRank %d ready to post MPI_Recv call!", myid);
		printf("\nmyid: %d \t data_arr2[0] = %d", myid, data_arr2[0]);
		printf("\nmyid: %d \t data_arr2[1] = %d", myid, data_arr2[1]);
		
		MPI_Irecv(data_arr, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
		MPI_Send(data_arr2, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
		
		MPI_Wait(&request,MPI_STATUS_IGNORE);
		
		printf("\nData received.");
		
		//Print received data
		printf("\nmyid: %d \t data_arr[0] = %d", myid, data_arr[0]);
		printf("\nmyid: %d \t data_arr[1] = %d", myid, data_arr[1]);
		
		printf("\n\nProgram exit!\n");	
	}
	
	printf("\nRank %d reached here - before MPI_Finalize!", myid);
	//End MPI environment        
	MPI_Finalize();
	printf("\nRank %d reached here - after MPI_Finalize!", myid);
}
