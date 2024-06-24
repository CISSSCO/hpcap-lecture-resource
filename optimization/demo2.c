#include<stdio.h>
inline int square(int x) {
    return x * x;
}
int main(){
    int x = 10;
    int y = square(x);
    printf("Square of %d : %d\n", x, y);
    return 0;
}
