#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){
    int i, j, myid, size, n = 400;
    int **m1, **m2, **sumMat;
    m1 = (int**)malloc(sizeof(int*) * n);
    m2 = (int**)malloc(sizeof(int*) * n);
    sumMat = (int**)malloc(sizeof(int*) * n);
    for(i = 0; i < n; i++){
        m1[i] = (int*)malloc(sizeof(int) * n);
        m2[i] = (int*)malloc(sizeof(int) * n);
        for(j = 0; j < n; j++){
            m1[i][j] = 1;
            m2[i][j] = 1;
        }
    }
    /*
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("%d ",m1[i][j]);
        }
        printf("\n");
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("%d ",m2[i][j]);
        }
        printf("\n");
    }*/

    for(i = 0; i < n; i++){
        sumMat[i] = (int*)malloc(sizeof(int) * n);
        for(j = 0; j < n; j++){
            sumMat[i][j] = m1[i][j] + m2[i][j];
        }
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("%d ",sumMat[i][j]);
        }
        printf("\n");
    }

    return 0;
}
