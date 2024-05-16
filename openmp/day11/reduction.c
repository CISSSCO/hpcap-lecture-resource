#include<stdio.h>
#define N 100
int main(){
  int a[N];
  long long sum = 0;
  for(int i = 0; i < N; i++) a[i] = i + 1;
  #pragma omp parallel for reduction(+:sum)
  for(int i = 0; i < N; i++){
    sum+= a[i];
  }

  printf("Sum = %lld\n", sum);
  printf("ActualSum = %d\n", (N * (N + 1)) / 2);
}
