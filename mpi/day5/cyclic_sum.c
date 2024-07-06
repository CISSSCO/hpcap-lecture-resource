#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, sum = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int number;
    if (rank == 0) {
        sum = 0;
        MPI_Send(&sum, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&sum, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Cyclic sum: %d\n", sum);
    } else if (rank == size - 1) {
        MPI_Recv(&sum, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        sum+= rank;
        MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else{
        MPI_Recv(&sum, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        sum+= rank;
        MPI_Send(&sum, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
