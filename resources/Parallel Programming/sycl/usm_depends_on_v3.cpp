#include <CL/sycl.hpp>
constexpr int N=16;

int main() {
    queue q;
    int *data1 =  malloc_shared<int>(N, q);
    int *data2 =  malloc_shared<int>(N, q);
    for(int i=0;i<N;i++) 
    {
        data1[i] = 10; 
        data2[i] = 10;
    }
    auto e1 = q.parallel_for(N, [=](auto i){
        data1[i] += 2;
    });
    auto e2 = q.parallel_for(N, [=](auto i){
        data2[i] += 3;
    });
    q.parallel_for(N, {e1,e2}, [=](auto i){
        data1[i] += data2[i];
    }).wait();
    for(int i=0;i<N;i++) 
    {
        std::cout << data[i] << " ";
    }
    free(data1, q); 
    free(data2, q);
}
