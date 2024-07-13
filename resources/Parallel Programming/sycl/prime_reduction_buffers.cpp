#include <CL/sycl.hpp>
constexpr int N=10000;
constexpr int B=100;
using namespace sycl;

int main() {
  queue q(cpu_selector_v);

  int count = 1;
  {
    buffer buf_cnt(&count, range(1));

    q.submit([&](handler& h) {
      auto reduction_sum = reduction(buf_cnt, h, plus<>());
      
      h.parallel_for(nd_range<1>{N, B}, reduction_sum, 
             [=](nd_item<1> it, auto& temp) {
                int flag = 0;
                int j;
                int i = it.get_global_id(0);
		if(i>2)
		{
			for(j=2;j<i;j++)	
			{
			    if((i%j) == 0)
			    {
				flag = 1;
				break;
			    }
			}
			if(flag == 0)
			{
				temp += 1;
			}
		}
      });
    });
  }
  std::cout << "count = " << count << std::endl;
}
