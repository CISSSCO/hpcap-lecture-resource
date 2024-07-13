#include <CL/sycl.hpp>
#define N 10000
#define B 100
using namespace sycl;

int main() {
  
  queue q(cpu_selector_v);
  int  flag;
  int * count = malloc_shared<int>(1, q);
  count[0] = 1; 

  q.parallel_for(nd_range<1>{N, B}, 
             reduction(count, plus<>()), [=](nd_item<1> it, auto& temp) {
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
  }).wait();
   
   
  std::cout << "count = " << count[0] << std::endl;
}
