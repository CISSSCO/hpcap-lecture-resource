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

    if (rank == 0) {
        int data[5] = {1, 2, 3, 4, 5};
        MPI_Send(data, 5, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent data to process 1\n");
    } else if (rank == 1) {
        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);

        int count;
        MPI_Get_count(&status, MPI_INT, &count);

        int *buffer = (int*)malloc(count * sizeof(int));
        MPI_Recv(buffer, count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process 1 received %d integers:\n", count);
        for (int i = 0; i < count; i++) {
            printf("%d ", buffer[i]);
        }
        printf("\n");

        free(buffer);
    }

    MPI_Finalize();
    return 0;
}
