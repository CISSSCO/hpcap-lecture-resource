#include <stdio.h>
#include <mpi.h>
#include<malloc.h>
//Include user defined header files

//Defines

//Global variables

//Pass argc and argv for main
int main (int argc, char *argv[])
 {
	//Int variables for Process number & number of processes .
	int  rank, size;

	//Intialize MPI
	MPI_Init (&argc, &argv);
	//Get number of processes
	MPI_Comm_size (MPI_COMM_WORLD, &size);
	//Get processes  number 
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	
	 MPI_Request *requestList,requestNull;
	 MPI_Status  status;
	
	//Array size = 10*number of workers
	int arr_size=10*(size-1);
	
	int master=0,worker,row=0,task;
	

/***************************Master***********************************/
	if(rank==master)
	{
		//Declare an array and total
		int array[arr_size],total=0,total1=0;
		
		requestList =(MPI_Request*)malloc((size-1)*sizeof(MPI_Request));
		
		//Intialize
		for(row=0;row<=arr_size;row++)
			array[row]=row;

		//Master sends array asynchronously to workers, it doesnt have to wait untill prev send has happened to send next
		for(worker=1;worker<size;worker++)
		{
		MPI_Isend(&array[(worker-1)*10],10,MPI_INT,worker,0,MPI_COMM_WORLD, &requestNull);
		}
	
		//Master recieves asynchronously from workers, it doesnt have to wait untill prev recv has happened to send next
		for(worker=1;worker<size;worker++)
		{	
			MPI_Irecv(&total,1,MPI_INT,worker,1,MPI_COMM_WORLD,&(requestList[worker-1]));
		}
		
		//Wait till all the workers partial sum is received
		for(task=1;task<size;task++)
		{
			int index; 
			MPI_Waitany(size-1, requestList, &index, &status);
			printf("Sum computed from the process%d: %d\n", index+1, total);
			total1+=total;
    		}	
		printf("%d is the sum of first %d numbers\n",total1,arr_size);
		printf("\n\n%d is the Expected sum of first %d numbers\n",(arr_size)*(arr_size-1)/2,arr_size);
  	
  	}
	
		
	
/***************************Worker***********************************/
	else  
	{
		int array[10],total=0;
		//Receive from master
		//MPI_Recv(void* data, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm communicator, MPI_Status* status)
		MPI_Recv(&array[0], 10,MPI_INT,master,master,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

		//Add
		for(row=0;row<10;row++)
			total+=array[row];

		//Send to master
		//MPI_Send(void* data, int count, MPI_Datatype datatype, int destination,int tag, MPI_Comm communicator) 
		MPI_Send(&total, 1, MPI_INT, master, 1, MPI_COMM_WORLD);
	}
	
	//Finalize MPI
	MPI_Finalize ();
	return 0;
 }
