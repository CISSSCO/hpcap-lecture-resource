//Include standard header files
#include <stdio.h>
#include <mpi.h>
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
	//Window for one sided communication
	MPI_Win win;
	//Array size = 10*number of workers-1
	int arr_size=10*(size-1);
	
	int master,worker,row=0;

	//Randomly select the master and Broadcast the master's rank
	if (rank == 0) 
	{
		master = rand() % size;
		printf("%d is Master\n", master);
	}
	//Broadcast master
	MPI_Bcast(&master, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	//Master task		
	if(rank==master)
	{
		//Declare an array and partial_sum
		int array[arr_size],partial_sum=0,sum=0;

		//Intialize
		for(row=0;row<=arr_size;row++)
			array[row]=row;
		
		//Put 10 elements in every worker
		row=0;
		//Creating NULL window
		MPI_Win_create(NULL,0,1,MPI_INFO_NULL,MPI_COMM_WORLD,&win);
		
		//Put 10 elements in every worker
		for(worker=0;worker<size;worker++)
			if(worker!=master)
			{
			MPI_Win_lock(MPI_LOCK_SHARED,worker,0,win);
			MPI_Put(&array[row*10],10,MPI_INT,worker,0,10,MPI_INT,win);
			/* Block until put succeeds */
			MPI_Win_unlock(worker,win);
			row++;
			}
		// Free the window
		MPI_Win_free(&win);
		
		//Null window for Receiving partial_sum from worker
		MPI_Win_create(NULL,0,1,MPI_INFO_NULL,MPI_COMM_WORLD,&win);
		//get partial sum and add it to final sum
		for(worker=0;worker<size;worker++)
		{	if(worker!=master)
			{
			MPI_Win_lock(MPI_LOCK_SHARED,worker,0,win);
			MPI_Get(&partial_sum,1,MPI_INT,worker,0,1,MPI_INT,win);
			// Block until put succeeds 
			MPI_Win_unlock(worker,win);
			sum+=partial_sum;
			}
		}
		//Free window
		MPI_Win_free(&win);
		printf("%d is the sum of first %d numbers\n",sum,arr_size);
	}
	
	else
	{
		int array[10],partial_sum=0;
		//Create window for 10 elements filled by master
		MPI_Win_create(&array[0],10*sizeof(int),sizeof(int),MPI_INFO_NULL, MPI_COMM_WORLD, &win);
		/* No sync calls on the target process! */
		MPI_Win_free(&win);
		
		//Add
		for(row=0;row<10;row++)
			partial_sum+=array[row];

		//Print
		printf("Sum calculated by process %d is %d\n",rank, partial_sum); 

		//Create window for partial sum, to be read by master
		MPI_Win_create(&partial_sum,sizeof(int),sizeof(int),MPI_INFO_NULL, MPI_COMM_WORLD, &win);
		/* No sync calls on the target process! */
		MPI_Win_free(&win);
		
	}
	
	//Finalize MPI
	MPI_Finalize ();
	return 0;
 }
