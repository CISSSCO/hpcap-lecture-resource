#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size_int, size_double, size_char, total_size;
    MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &size_int);
    MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &size_double);
    MPI_Pack_size(1, MPI_CHAR, MPI_COMM_WORLD, &size_char);

    total_size = size_int + size_double + size_char;
    printf("Buffer size required for packing: %d bytes\n", total_size);

    MPI_Finalize();
    return 0;
}
