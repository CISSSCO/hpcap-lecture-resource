#include <CL/sycl.hpp>
constexpr int N=16;
constexpr int B=16;
using namespace sycl;

int main() {
    queue q;

  std::vector<int> data(N);
  for (int i = 0; i < N; i++) data[i] = i;
  int sum = 0, min = 0;
  {
    buffer buf_data(data);
    buffer buf_sum(&sum, range(1));
    buffer buf_min(&min, range(1));

    q.submit([&](handler& h) {
      accessor acc_data(buf_data, h, read_only);
        
      auto reduction_sum = reduction(buf_sum, h, plus<>());
      auto reduction_min = reduction(buf_min, h, minimum<>());
      
      h.parallel_for(nd_range<1>{N, B}, reduction_sum, reduction_min, 
             [=](nd_item<1> it, auto& temp_sum, auto& temp_min) {
        auto i = it.get_global_id();
        temp_sum.combine(acc_data[i]);
        temp_min.combine(acc_data[i]);
      });
    });
  }
  std::cout << "sum = " << sum << "\n min = " << min << std::endl;
  
}
