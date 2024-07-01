#include"stdio.h"
#include"mpi.h"
#define N 100

int main()
{
	int myid, size;
	int myval;

    int arr[N];
	//Initialize MPI environment
	MPI_Init(NULL,NULL);

	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Get my unique ID among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	// Process with ID exactly equal to 0
	if(myid==0){
		//Initialize data to be sent
        for(int i = 0; i < N; i++) arr[i] = i + 1;
		//Send data
		MPI_Send(arr, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("\nmyid: %d \t Data sent.\n", myid);
	}
	else if(myid==1){	// Process with ID exactly equal to 1
		//Initialize receive array to some other data
		MPI_Recv(arr, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("\nmyid: %d \t Data received.\n", myid);
		//Print received data
        for(int i = 0; i < N; i++)
          printf("%d ", arr[i]);
	}

	//End MPI environment
	MPI_Finalize();
}
