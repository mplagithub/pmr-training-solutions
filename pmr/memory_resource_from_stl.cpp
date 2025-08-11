#include <iostream>
#include <list>
#include <memory>
#include <memory_resource>
#include <new>
#include <vector>

int main() {
  // std::pmr::set_default_resource(std::pmr::null_memory_resource());

  static constexpr auto kBufSize = 16;
  unsigned char c_buffer[kBufSize];

  // or use constructor with upstream specified
  std::pmr::monotonic_buffer_resource myBuffer{c_buffer, kBufSize};

  std::cout << "--- Allocating/Deallocating for vectors ---\n";
  std::pmr::vector<int> v1(4, &myBuffer);

  for (int i = 0; i < 4; ++i) {
    v1.push_back(i);
  }
  std::cout << static_cast<void*>(c_buffer) << std::endl;
  std::cout << v1.data() << std::endl;
  return 0;
}