#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int Buffer;
    if (rank == 0) {
        Buffer = 100;
        MPI_Sendrecv(&Buffer, 1, MPI_INT, 1, 0, &Buffer, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received number %d\n", Buffer);
    } else if (rank == 1) {
        Buffer = 200;
        MPI_Sendrecv(&Buffer, 1, MPI_INT, 0, 0, &Buffer, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received number %d\n", Buffer);
    } else {
        printf("I am process %d and I have nothing to do\n", rank);
    }

    MPI_Finalize();
    return 0;
}
