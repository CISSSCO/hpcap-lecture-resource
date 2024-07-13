#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]) {
    int rank, size, message;
    // Initialize MPI
    MPI_Init(&argc, &argv);
    // Get the rank of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // Get the total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size < 2) {
        fprintf(stderr, "This program requires at least two processes.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    if (rank == 0) {
        // Process 0 sends a message
        message = 42;
        MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent the message: %d\n", message);
    } else if (rank == 1) {
        // Process 1 receives the message
        MPI_Recv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received the message: %d\n", message);
    }
    // Finalize MPI
    MPI_Finalize();
    return 0;
}

