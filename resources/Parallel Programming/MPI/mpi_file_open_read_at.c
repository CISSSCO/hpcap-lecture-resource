#include <stdio.h>
#include "mpi.h"
int main(int argc, char *argv[])
{
    MPI_File fh;
    int buf[1000], rank;
    int i;
    MPI_Offset filesize;
    int nints, offset, nprocs, count;
    MPI_Status status;
    
    MPI_Init(0,0);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_File_open(MPI_COMM_WORLD, "test.out", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
    
    MPI_File_get_size(fh,&filesize);
    
    nints = filesize / (nprocs*sizeof(int));
    offset = rank * nints * sizeof(int);
    MPI_File_read_at(fh, offset, buf, nints, MPI_INT, &status);
    MPI_Get_count(&status, MPI_INT, &count);
    printf("process %d read %d ints\n", rank, count);
    
    MPI_File_close(&fh);
    MPI_Finalize();
return 0;
}
