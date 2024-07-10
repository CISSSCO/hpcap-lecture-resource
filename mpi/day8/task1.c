#include <mpi.h>
#include <stdio.h>

long long sumOfSquares(long long *arr, int size){
    long long sum = 0;
    for(int i = 0; i < size; i++){
        sum+= arr[i] * arr[i] * 1L;
    }
    return sum;
}

long long sum(long long *arr, int size){
    long long sum = 0;
    for(int i = 0; i < size; i++){
        sum+= arr[i] * 1L;
    }
    return sum;
}


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

    //printf("World Rank: %d, New Rank: %d, New Size: %d\n", world_rank, new_rank, new_size);
    const int data_size = 1000000;
    long long data[data_size];
    if(new_rank == 0){
        for(int i = 0; i < data_size; i++){
            data[i] = i + 1;
        }
    }
    //data broadcasted to each process in new_comm
    int chunk_size = data_size / new_size;
    long long local_array[chunk_size];
    long long local_sum = 0;
    long long local_square_sum = 0;
    MPI_Scatter(data, chunk_size, MPI_LONG_LONG, local_array, chunk_size, MPI_LONG_LONG, 0, new_comm);
    // Perform some communication within the new communicator
    if(color == 0){
        local_sum = sum(local_array, chunk_size);
    }
    if(color == 1){
        local_square_sum = sumOfSquares(local_array, chunk_size);
    }
    long long final_sum = 0;
    long long final_square_sum = 0;
    MPI_Allreduce(&local_sum, &final_sum, 1, MPI_LONG_LONG, MPI_SUM, new_comm);
    MPI_Allreduce(&local_square_sum, &final_square_sum, 1, MPI_LONG_LONG, MPI_SUM, new_comm);
    if(new_rank == 0){
        if(color == 0)
            printf("World Rank: %d, Sum of arrays: %lld\n", world_rank, final_sum);
        if(color == 1)
            printf("World Rank: %d, Sum of squares of arrays: %lld\n", world_rank, final_square_sum);
    }

    // Free the new communicator and group
    MPI_Comm_free(&new_comm);

    MPI_Finalize();
    return 0;
}
