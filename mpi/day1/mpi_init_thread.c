#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int provided;

    // Initialize the MPI environment with thread support
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);

    // Check the level of thread support provided
    if (provided < MPI_THREAD_MULTIPLE) {
        printf("MPI does not provide required thread support\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Print off a hello world message
    printf("Hello world from processor %d out of %d processors with thread support level %d\n", world_rank, world_size, provided);

    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}
