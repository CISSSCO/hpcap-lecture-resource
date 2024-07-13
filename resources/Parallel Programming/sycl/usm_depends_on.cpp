#include <CL/sycl.hpp>
constexpr int N=16;

int main() 
{
    queue q;
    int *data =  malloc_shared<int>(N, q);
    for(int i=0;i<N;i++) 
    {
        data[i] = 10;
    }
    auto e1 = q.submit([&] (handler &h){
        h.parallel_for(N, [=](auto i){
            data[i] += 2;
        });
    });
    auto e2 = q.submit([&] (handler &h){
        h.depends_on(e1);
        h.parallel_for(N, [=](auto i){
            data[i] += 3;
        });
    });
    q.submit([&] (handler &h){
        h.depends_on(e2);
        h.parallel_for(N, [=](auto i){
            data[i] += 5;
        });
    }).wait();
    for(int i=0;i<N;i++) 
    {
        std::cout << data[i] << " ";
    }
    free(data, q);
}
