/* Try to read and analyze the code and also change some of the parameters
 * according to your needs. I have also added comments to make you aware of my
 * thought process while doing the code.*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 100000

//function to calculate sum
void sum(int* arr, int start, int end, int* result) {
    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += arr[i];
    }
    *result = sum;
}

//function to calculate totalSum
void totalSum(int* result, int size, int* total) {
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum+= result[i];
    }
    *total = sum;
}

int main() {
    omp_set_num_threads(5); //setting total number of threads
    int* arr = (int*) malloc(N * sizeof(int));  //creating and allocating array
    int *result, total = 0;
    int start = 0, end = 0;

    //allocating spaces for resultant sum array
    //I want to store the sum by each task at a specific thread index
    //Here size of resultant array will be equal to total_no_of_threads
    //because each thread will do task of calculating there some and store 
    //it in there location which will be result[threadId]
    result = (int*) malloc(omp_get_num_threads() * sizeof(int)); 

    // Initialize the array
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    int chunksize = 0;
    #pragma omp parallel 
    {
        //here chunksize will be equal to N / total number of threads
        chunksize = N / omp_get_num_threads();
        #pragma omp single
        {
            for(int i = 0; i < omp_get_num_threads(); i++){
                //first task will start from 0 to chunksize
                //second task will start from 1 * chunsize to its (start + chunksize)
                start = i * chunksize;
                if(i == omp_get_num_threads() - 1){
                    //if your thread is last thread then we want to give all the remaining
                    //iterations to last threads if there's any reminder threads
                    end = N;
                }
                else{
                    end = start + chunksize;
                }
                //creating tasks here and storing the result in result[i]
                #pragma omp task
                sum(arr, start, end, &result[i]);
            }
            //taskwait for synchronization
            //try to remove taskwait and analyze the result
            //your code more likely to be involved in race condition
            #pragma omp taskwait
            //task for final sum calculation
            //below I used omp_get_num_threads to give the total size of result array
            //which in my case will be equal to total number of threads
            //bcz I created tasks equal to total number of threads
            #pragma omp task 
            totalSum(result, omp_get_num_threads(), &total);
        }

    }

    //printing total sum by tasking and by natural number sum formula
    printf("Total sum by tasking: %d\n", total);
    printf("Total sum by formula: %d\n", (N * (N + 1)) / 2);

    //resources deallocation
    free(arr);
    free(result);
    return 0;
}

