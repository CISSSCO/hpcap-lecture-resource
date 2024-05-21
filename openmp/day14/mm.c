#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define N 3000
int main(){
    int **a, **b, **c, **cp;

    //dynamic memory allocation
    a = (int**) malloc(sizeof(int*) * (N * N));
    b = (int**) malloc(sizeof(int*) * (N * N));
    c = (int**) malloc(sizeof(int*) * (N * N));
    cp = (int**) malloc(sizeof(int*) * (N * N));
    for(int i = 0; i < N; i++){
        a[i] = (int*) malloc(sizeof(int) * N);
        b[i] = (int*) malloc(sizeof(int) * N);
        c[i] = (int*) malloc(sizeof(int) * N);
        cp[i] = (int*) malloc(sizeof(int) * N);
    }

    //initilization of data
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            a[i][j] = rand() % 100 + 1;
            b[i][j] = rand() % 100 + 1;
            c[i][j] = 0;
            cp[i][j] = 0;
        }
    }

    //matrix addition serial
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    // Parallel matrix addition using OpenMP
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cp[i][j] = a[i][j] + b[i][j];
        }
    }

    //printing the result
    printf("Serial Addition: \n");
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    printf("-------------------------------------------------\n");

    //printing the parallel result
    printf("Parallel Addition: \n");
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d ", cp[i][j]);
        }
        printf("\n");
    }
    printf("-------------------------------------------------\n");

    //checking the validity of the parallel result
    int flag = 1;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(c[i][j] != cp[i][j]){
                flag = 0;
                break;
            }
        }
    }

    if(flag)
        printf("_____Passed_____\n");
    else printf("_____Failed_____\n");

    for (int i = 0; i < N; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
        free(cp[i]);
    }

    free(a);
    free(b);
    free(c);
    free(cp);

    return 0;
}
