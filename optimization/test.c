#include<stdio.h>
int main(){
    int x;
    for(int i = 0; i < 1000000; i++){
        int x = 10;
        x+= i;
    }
    printf("x = %d\n", x);
}
