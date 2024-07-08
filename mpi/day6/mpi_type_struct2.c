#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int arr[3];
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
    MPI_Datatype struct_type;

    // Create the datatype for my_struct
    int blocklengths[3] = {2, 1, 1};  // Sending part of the array, the double, and the char
    MPI_Aint displacements[3];
    MPI_Datatype types[3] = {MPI_INT, MPI_DOUBLE, MPI_CHAR};

    displacements[0] = offsetof(my_struct, arr);
    displacements[1] = offsetof(my_struct, b);
    displacements[2] = offsetof(my_struct, c);

    MPI_Type_create_struct(3, blocklengths, displacements, types, &struct_type);
    MPI_Type_commit(&struct_type);

    if (rank == 0) {
        data.arr[0] = 1;
        data.arr[1] = 2;
        data.arr[2] = 3;
        data.b = 3.14;
        data.c = 'A';

        MPI_Send(&data, 1, struct_type, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 has struct: {arr = [%d, %d, %d], b = %.2f, c = %c}\n", data.arr[0], data.arr[1], data.arr[2], data.b, data.c);
    } else if (rank == 1) {
        // Initialize the struct to zero
        data.arr[0] = data.arr[1] = data.arr[2] = 0;
        data.b = 0.0;
        data.c = '0';

        MPI_Recv(&data, 1, struct_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received struct: {arr = [%d, %d, %d], b = %.2f, c = %c}\n", data.arr[0], data.arr[1], data.arr[2], data.b, data.c);
    }

    MPI_Type_free(&struct_type);
    MPI_Finalize();
    return 0;
}
