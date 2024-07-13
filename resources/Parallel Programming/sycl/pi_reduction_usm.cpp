#include <CL/sycl.hpp>
#define N 90000
#define B 100
using namespace sycl;

int main() {
  
  queue q(cpu_selector_v);
   float pi, step;  
  step = 1.0/( float)N;
  float * sum = malloc_shared< float>(1, q);
  sum[0] = 0.0; 

  q.parallel_for(nd_range<1>{N, B}, 
             reduction(sum, plus<>()), [=](nd_item<1> it, auto& temp) {
                int i = it.get_global_id(0);
                 float x = (i)*step;
                temp += 4.0/(1.0+x*x);
  }).wait();
   
  pi = step*sum[0];  
  std::cout << "pi = " << pi << std::endl;
}
