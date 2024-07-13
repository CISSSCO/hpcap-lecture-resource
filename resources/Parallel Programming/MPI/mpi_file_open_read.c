#include <stdio.h>
#include "mpi.h"
int main(int argc, char *argv[])
{
    MPI_File fh;
    int buf[1000], rank;
    int i;
    
    
    MPI_Init(0,0);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_File_open(MPI_COMM_WORLD, "test.out", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
    if (rank == 0)
    {
        MPI_File_read(fh, buf, 1000, MPI_INT, MPI_STATUS_IGNORE);
        for(i=0;i<1000;i++)
        {
            printf("\t %d ", buf[i]);
        }    
    }
    MPI_File_close(&fh);
    MPI_Finalize();
return 0;
}
