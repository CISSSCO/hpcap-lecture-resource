#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        fprintf(stderr, "World size must be greater than 1 for this example\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int array_size = 10;
    int* array = (int*)malloc(array_size * sizeof(int));

    if (rank == 0) {
        // Initialize the array with some values
        for (int i = 0; i < array_size; i++) {
            array[i] = i + 1;
        }

        int buffer_size = MPI_BSEND_OVERHEAD + array_size * sizeof(int);
        void* buffer = malloc(buffer_size);
        MPI_Buffer_attach(buffer, buffer_size);

        MPI_Bsend(array, array_size, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent array to process 1\n");

        MPI_Buffer_detach(&buffer, &buffer_size);
        free(buffer);
    } else if (rank == 1) {
        MPI_Recv(array, array_size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received array from process 0: ");
        for (int i = 0; i < array_size; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
    }

    free(array);

    MPI_Finalize();
    return 0;
}
