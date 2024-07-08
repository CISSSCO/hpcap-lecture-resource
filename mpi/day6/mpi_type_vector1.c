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

    const int count = 3;       // Number of blocks
    const int blocklength = 2; // Number of elements in each block
    const int stride = 5;      // Number of elements between the start of each block
    MPI_Datatype vector_type;

    // Create a vector datatype
    MPI_Type_vector(count, blocklength, stride, MPI_INT, &vector_type);
    MPI_Type_commit(&vector_type);

    if (rank == 0) {
    int data[15];              // Array to send/receive
        // Initialize the data array with some values
        for (int i = 0; i < 15; i++) {
            data[i] = i + 1;
        }

        MPI_Send(data, 1, vector_type, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent data: ");
        for (int i = 0; i < 15; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
    } else if (rank == 1) {
        int data1[6];

        MPI_Recv(data1, count * blocklength, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received data: ");
        for (int i = 0; i < 6; i++) {
            printf("%d ", data1[i]);
        }
        printf("\n");
    }

    MPI_Type_free(&vector_type);
    MPI_Finalize();
    return 0;
}
