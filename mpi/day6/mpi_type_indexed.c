#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        fprintf(stderr, "World size must be greater than 1 for this example\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    const int count = 3;
    int blocklengths[3] = {1, 2, 1};
    int displacements[3] = {0, 3, 7};
    int data[10];
    MPI_Datatype indexed_type;

    // Create an indexed datatype
    MPI_Type_indexed(count, blocklengths, displacements, MPI_INT, &indexed_type);
    MPI_Type_commit(&indexed_type);

    if (rank == 0) {
        // Initialize the data array with some values
        for (int i = 0; i < 10; i++) {
            data[i] = i + 1;
        }

        MPI_Send(data, 1, indexed_type, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent data: ");
        for (int i = 0; i < 10; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
    } else if (rank == 1) {
        // Initialize the data array to zero
        for (int i = 0; i < 10; i++) {
            data[i] = 0;
        }

        MPI_Recv(data, 1, indexed_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received data: ");
        for (int i = 0; i < 10; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
    }

    MPI_Type_free(&indexed_type);
    MPI_Finalize();
    return 0;
}
