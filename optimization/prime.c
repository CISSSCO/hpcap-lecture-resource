#include<stdio.h>
int main(){
    int x = 2825899233;
    int flag = 1;
    for(int i = 2; i < x; i++){
        if(x % i == 0){
            flag = 0;
            break;
        }
    }
    if(flag) printf("Prime\n");
    else printf("not prime\n");
    return 0;
}
