#include <sycl/sycl.hpp>

constexpr int num=100;
using namespace sycl;

  int main() {
  auto R = range<1>{ num };
  //Create Buffers A and B
  buffer<int> A{ R }, B{ R }, C{ R };
  //Create a device queue
  queue Q(gpu_selector_v);

  //# Print the device name
  std::cout << "Device: " << Q.get_device().get_info<info::device::name>() << "\n";

  
  // Initialize the data    
  Q.submit([&](handler& h) {
    accessor outa(A,h,write_only);
    accessor outb(B,h,write_only);
    h.parallel_for(R, [=](auto idx) {
      outa[idx] = idx[0];
      outb[idx] = idx[0];
    }); });
   
      
  Q.submit([&](handler& h) {
    accessor outa(A,h,read_only);
    accessor outb(B,h,read_only);
    accessor outc(C,h,write_only);
    h.parallel_for(R, [=](auto idx) {
      outc[idx] = outa[idx] + outb[idx]; }); });

 // And the following is back to device code
 host_accessor result(C,read_only);
  for (int i=0; i<num; ++i)
    std::cout << result[i] << "\t";      
  return 0;
}
