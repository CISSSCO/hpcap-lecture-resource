#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

//Defines
#define SEED 35791246		//Seed to generate random number
#define ITER 1000000		//Number of iterations
#define PI 3.141592653589793	//Original PI value


void main(int argc, char *argv[])
{
	int rank,size,master=0,nthreads;
	
	//Intailize MPI
	MPI_Init(&argc,&argv);
	
	//Total number of process
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	//Process id ie rank
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
	double pi;
	//Initialize random numbers
	srand(SEED);
	
	int cnt,partial_count=0;
	double x,y;
	
	#pragma omp parallel num_threads(4) reduction(+:partial_count)
	{
		int tid = omp_get_thread_num();
		nthreads = omp_get_num_threads();
		#pragma omp for
		for (cnt=rank; cnt<ITER;cnt+=size)		
		//Dividing work to process (slicing) for mpi process and internally by omp for threads
		{
			//Select X and Y randomly in 1st quad
			x = (double)rand()/RAND_MAX;
			y = (double)rand()/RAND_MAX;
		
			//Check if it falls under the curve of radius 1 unit
			if ((x*x+y*y)<=1)
				partial_count++;
		}
		printf ("Partial count by tid %d of rank %d is %d\n",tid,rank,partial_count);
	}
	//Workers sends partial count to master
	if (rank!=master)
	//MPI_Send(void* data, int count, MPI_Datatype datatype, int destination,int tag, MPI_Comm communicator) 
	MPI_Send(&partial_count,1, MPI_INT,master, 0, MPI_COMM_WORLD);
	
	//Master
	else
	{
		int worker,count;
		count=partial_count;
		//Receive partail counts from workers and add to sum
		for(worker=1;worker<size;worker++)
		{	
			//MPI_Recv(void* data, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm communicator, MPI_Status* status)
			MPI_Recv(&partial_count, 1,MPI_INT,worker,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			count+=partial_count;
		}
	
		//pi=Number of points falling under curve/Total points * Number of quadrants
		pi=(double)count/ITER*4;
	
		printf("\nFor %d iterations by %d process\n",ITER,size);
		printf("computed pi value =\t\t%lf \n",pi);
		printf("Difference from original PI =\t\t%lf\n\n",PI-pi);
	}
	MPI_Finalize();
}

