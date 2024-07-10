#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Split the world group into two groups
    int color = world_rank % 2;  // Determine color based on rank
    MPI_Comm new_comm;
    MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &new_comm);

    // Get the new rank and size in the new communicator
    int new_rank, new_size;
    MPI_Comm_rank(new_comm, &new_rank);
    MPI_Comm_size(new_comm, &new_size);

    printf("World Rank: %d, New Rank: %d, New Size: %d\n", world_rank, new_rank, new_size);

    // Perform some communication within the new communicator
    int send_data = new_rank;
    int recv_data;
    MPI_Allreduce(&send_data, &recv_data, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    printf("World Rank: %d, New Comm Sum: %d\n", world_rank, recv_data);

    // Free the new communicator and group
    MPI_Comm_free(&new_comm);

    MPI_Finalize();
    return 0;
}
