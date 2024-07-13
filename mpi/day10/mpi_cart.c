#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int dims[2] = {0, 0};
    MPI_Dims_create(size, 2, dims); // Automatically create a balanced 2D grid
    int periods[2] = {0, 0}; // No wrap-around connections
    MPI_Comm cart_comm;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &cart_comm);

    int coords[2];
    MPI_Cart_coords(cart_comm, rank, 2, coords);
    printf("Rank %d has coordinates (%d, %d)\n", rank, coords[0], coords[1]);

    // Cleanup
    MPI_Comm_free(&cart_comm);

    MPI_Finalize();
    return 0;
}
