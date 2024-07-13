#include"stdio.h"
#include"stdlib.h"
#include"mpi.h"

#define N 8
int main(int argc, char **argv)
{
	int myid, size;
	int *A, *B, *C; 
	int *a, *c;
	int i,j;
	int flag = 0;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	B = (int *) malloc(N*sizeof(int));
	
	if(myid == 0)
	{
	    A = (int *) malloc(N*N*sizeof(int));	    
	    C = (int *) malloc(N*sizeof(int));
	    for(i=0;i<N;i++)
	    {
	        for(j=0;j<N;j++)
	        {
	            A[i*N+j] = 1;
	        }
	        B[i] = 1;
	        C[i] = 0; 
	    }
	}
	a = (int *) malloc((N*N)/size*sizeof(int));
	c = (int *) malloc((N)/size*sizeof(int));
	
	MPI_Scatter(A, (N*N)/size, MPI_INT, a, (N*N)/size, MPI_INT, 0, MPI_COMM_WORLD);
	//MPI_Scatter(B, (N*N)/size, MPI_INT, b, (N*N)/size, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(B, N, MPI_INT, 0, MPI_COMM_WORLD);	
	for(i=0;i<N/size;i++)
	{
	    c[i] = 0;
	    for(j=0;j<N;j++)
	    {
	        c[i] += a[i*N+j] * B[j]; 
	    }
	}
	
	MPI_Gather(c, N/size, MPI_INT, C, N/size, MPI_INT, 0, MPI_COMM_WORLD);
	
	if(myid == 0)
	{
	    for(i=0;i<N;i++)
	    {
	        if(C[i] != N)
	        {
	            flag = 1;
	            printf("\n %d", C[i]);
	            break;
	        } 
	    }
	    if(flag == 0)
	    {
	        printf("\n PASS!\n");
	    }
	    else
	    {
	        printf("\n FAIL!\n");
	    }
	    free(A);
	    free(C);
    }    
	MPI_Finalize();
	free(a);
	free(B);
	free(c);
}
