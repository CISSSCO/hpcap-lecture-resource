  #include <CL/sycl.hpp>
  using namespace sycl;
  constexpr int N=16;

  void kernel_code(std::vector<int> &v, queue &q){  
    buffer buf(v);
    q.submit([&](handler& h) {
      accessor a(buf, h);
      h.parallel_for(N, [=](auto i) {
        a[i] -= 2;
      });
    });
  }

  int main() {    
    std::vector<int> v(N, 10);
    queue q;
    kernel_code(v,q);    
    for (int i = 0; i < N; i++)
        std::cout << v[i] << "\n";
    return 0;
  }

