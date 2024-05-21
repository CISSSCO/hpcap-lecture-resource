#include<stdio.h>
#include<stdlib.h>
#define N 30
int main(){
    int **a, **b, **c;

    //dynamic memory allocation
    a = (int**) malloc(sizeof(int*) * (N * N));
    b = (int**) malloc(sizeof(int*) * (N * N));
    c = (int**) malloc(sizeof(int*) * (N * N));
    for(int i = 0; i < N; i++){
        a[i] = (int*) malloc(sizeof(int) * N);
        b[i] = (int*) malloc(sizeof(int) * N);
        c[i] = (int*) malloc(sizeof(int) * N);
    }

    //initilization of data
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            a[i][j] = rand() % 100 + 1;
            b[i][j] = rand() % 100 + 1;
            c[i][j] = 0;
        }
    }

    //matrix addition
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    //printing the result
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    return 0;
}
