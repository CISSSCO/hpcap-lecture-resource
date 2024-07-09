#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    double b;
    char c;
} my_struct;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        fprintf(stderr, "World size must be greater than 1 for this example\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    my_struct data;
    int buffer_size, position;
    void *buffer;

    if (rank == 0) {
        data.a = 42;
        data.b = 3.14;
        data.c = 'A';

        // Calculate the buffer size required for packing
        MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &buffer_size);
        buffer_size += sizeof(double) + sizeof(char); // Adding the sizes of the other data types
        buffer = malloc(buffer_size);

        position = 0;
        MPI_Pack(&data.a, 1, MPI_INT, buffer, buffer_size, &position, MPI_COMM_WORLD);
        MPI_Pack(&data.b, 1, MPI_DOUBLE, buffer, buffer_size, &position, MPI_COMM_WORLD);
        MPI_Pack(&data.c, 1, MPI_CHAR, buffer, buffer_size, &position, MPI_COMM_WORLD);

        MPI_Send(buffer, position, MPI_PACKED, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent packed data\n");

        free(buffer);
    } else if (rank == 1) {
        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_PACKED, &buffer_size);

        buffer = malloc(buffer_size);
        MPI_Recv(buffer, buffer_size, MPI_PACKED, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        position = 0;
        MPI_Unpack(buffer, buffer_size, &position, &data.a, 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Unpack(buffer, buffer_size, &position, &data.b, 1, MPI_DOUBLE, MPI_COMM_WORLD);
        MPI_Unpack(buffer, buffer_size, &position, &data.c, 1, MPI_CHAR, MPI_COMM_WORLD);

        printf("Process 1 received unpacked data: {a = %d, b = %.2f, c = %c}\n", data.a, data.b, data.c);
        free(buffer);
    }

    MPI_Finalize();
    return 0;
}
