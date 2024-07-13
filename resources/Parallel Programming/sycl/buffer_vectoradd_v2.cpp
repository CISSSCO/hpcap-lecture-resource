#include <CL/sycl.hpp>
constexpr int N=16;
using namespace sycl;
int main() {
	std::vector<int> a(N);
	std::vector<int> b(N);
	std::vector<int> c(N);
	for(int i = 0;i<N;i++)
	{
	    a[i]=i;
	    b[i]=i;
	    c[i]=0;
	}
	{
	  buffer a_buf(a);
	  buffer b_buf(b);
	  buffer c_buf(c);
	  queue q;
	  
	  q.submit([&](handler& h) {
	    accessor A(a_buf, h, read_only);
	    accessor B(b_buf, h, read_only);
	    accessor C(c_buf, h, write_only);
	    h.parallel_for(N, [=](auto i) {
		    C[i] = A[i] + B[i];
	    });
	  });
	}
    for (int i=0; i<N; ++i) 
    {
	  std::cout << c[i] << "\t";
    }
}
