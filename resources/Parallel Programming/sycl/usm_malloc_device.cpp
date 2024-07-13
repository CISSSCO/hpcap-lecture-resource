#include <CL/sycl.hpp>
using namespace sycl;
constexpr int N = 16;

int main() 
{
    sycl::queue q;
    int data[N]; 
    for (int i=0;i<N;i++)
    { 
        data[i] = 10;
    }
    
    auto data_d = sycl::malloc_device<int>(N, q);
    
    q.memcpy(data_d, data, sizeof(int) * N).wait();
    
    q.parallel_for(N, [=](auto i) { 
      data_d[i] += 1; 
    }).wait();
    
    q.memcpy(data, data_d, sizeof(int) * N).wait();
    
    for(int i=0;i<N;i++)
    {
        std::cout << data[i] << " ";
    }
    sycl::free(data_d, q);
}
