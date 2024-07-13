#include <CL/sycl.hpp>
constexpr int N=90000;
constexpr int B=100;
using namespace sycl;

int main() {
  queue q(cpu_selector_v);

  float sum = 0.0;
  float pi, step;  
  step = 1.0/( float)N;
  {
    buffer buf_sum(&sum, range(1));

    q.submit([&](handler& h) {
      auto reduction_sum = reduction(buf_sum, h, plus<>());
      
      h.parallel_for(nd_range<1>{N, B}, reduction_sum, 
             [=](nd_item<1> it, auto& temp_sum) {
                int i = it.get_global_id(0);
                float x = (i)*step;
                temp_sum.combine(4.0/(1.0+x*x));
      });
    });
  }
  pi = step*sum;  
  std::cout << "pi = " << pi << std::endl;
}
