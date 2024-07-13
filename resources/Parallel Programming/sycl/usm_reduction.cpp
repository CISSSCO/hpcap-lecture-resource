#include <CL/sycl.hpp>
constexpr int N=16;
constexpr int B=4;

using namespace sycl;

int main() {
  
  queue q;
  auto data = malloc_shared<int>(N, q);
  for (int i = 0; i < N; i++) data[i] = i;

  auto sum = malloc_shared<int>(1, q);
  sum[0] = 0; 

  q.parallel_for(nd_range<1>{N, B}, 
             reduction(sum, plus<>()), [=](nd_item<1> it, auto& temp) {
       int i = it.get_global_id(0);
       temp += data[i];
  }).wait();

  std::cout << "Sum = " << sum[0] << std::endl;
}
