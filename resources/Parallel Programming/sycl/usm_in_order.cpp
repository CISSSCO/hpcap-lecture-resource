#include <CL/sycl.hpp>
constexpr int N=16;

int main() {
    queue q{property::queue::in_order()};
    int *data =  malloc_shared<int>(N, q);
    for(int i=0;i<N;i++) 
    {
        data[i] = 10;
    }
    
    q.parallel_for(N, [=](auto i){
        data[i] += 2;
    });

    q.parallel_for(N, [=](auto i){
        data[i] += 3;
    });

    q.parallel_for(N, [=](auto i){
        data[i] += 5;
    }).wait();

    for(int i=0;i<N;i++) 
    {
        std::cout << data[i] << " ";
    }
    free(data, q);
}
