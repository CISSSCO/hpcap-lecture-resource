#include<stdio.h>
void test(){
    printf("inside test\n");
    void t3(){
        printf("inside t3 which is already inside test\n");
    }
    t3();
}
int main(){
    test();
    return 0;
}

