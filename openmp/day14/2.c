#include<stdio.h>
#include<stdlib.h>
#define N 50000
int main(){
    int **a, **b, **c;
    a = (int**) malloc(sizeof(int*) * N);
    b = (int**) malloc(sizeof(int*) * N);
    c = (int**) malloc(sizeof(int*) * N);
    for(int i = 0; i < N; i++){
        a[i] = (int*) malloc(sizeof(int) * N);
        b[i] = (int*) malloc(sizeof(int) * N);
        c[i] = (int*) malloc(sizeof(int) * N);
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            a[i][j] = rand() % 100 + 1;
            b[i][j] = rand() % 100 + 1;
            c[i][j] = 0;
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    int flag = 1;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(c[i][j] != a[i][j] + b[i][j]){
                flag = 0;
                break;
            }
        }
    }
    if(flag == 1) printf("_____Passed_____\n");
    else printf("_____Failed_____\n");

}

