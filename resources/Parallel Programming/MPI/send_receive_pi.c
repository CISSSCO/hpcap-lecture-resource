#include"stdio.h"
#include"mpi.h"
#include<math.h> 

#include<sys/time.h>

#define N 999999999

int main(int argc, char **argv)
{
	int myid, size;
	int start, end, i;
	double dx, x, y, area, pi, recv_area;
	
	double exe_time;
	struct timeval stop_time, start_time;
	
	dx = 1.0/N;
	x = 0.0;
	area = 0.0;
 
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	start = myid * (N/size);
	end = start + (N/size);
	
	if(myid == (size - 1))
	{
	    end = N;
	}
	if(myid == 0)
	{
	    gettimeofday(&start_time, NULL);
	}
	
	for(i=start;i<end;i++)
	{
		x = i*dx;
		y = sqrt(1-x*x);
		area += y*dx;
	}
    
    if(myid==0)
	{
		for(i=1;i<size;i++)
	    {
	        MPI_Recv(&recv_area, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	        area = area + recv_area;
	    }
	    gettimeofday(&stop_time, NULL);	
	    exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));
	
	    pi = 4.0*area;
	    printf("\n Value of pi is = %.16lf\n Execution time is = %lf seconds\n", pi, exe_time);
	}
	else
	{
		MPI_Send(&area, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
	
	
	//End MPI environment        
	MPI_Finalize();
}
