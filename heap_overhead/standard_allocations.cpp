#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

// also:
// strace ./standard_allocations 2>&1 | grep mmap

int main() {
  using namespace std::chrono;

  constexpr int N = 100'000;
  constexpr size_t SMALL_SIZE = 32;
  constexpr size_t LARGE_SIZE = 100 * 1024 * 1024;  // 100 MB

  std::vector<void*> ptrs;
  ptrs.reserve(N);

  // Small allocations
  std::cout << "Benchmark: Small allocations " << SMALL_SIZE << "bytes "
            << " * " << N << " ~= " << (SMALL_SIZE * N) / (1024 * 1024)
            << "MB \n";
  auto t1 = high_resolution_clock::now();
  for (int i = 0; i < N; ++i) {
    ptrs.push_back(::operator new(SMALL_SIZE));
  }
  auto t2 = high_resolution_clock::now();
  for (void* p : ptrs) ::operator delete(p);
  auto t3 = high_resolution_clock::now();

  std::cout << "Allocated " << N << " small blocks in "
            << duration_cast<milliseconds>(t2 - t1).count() << " ms\n";
  std::cout << "Deallocated " << N << " small blocks in "
            << duration_cast<milliseconds>(t3 - t2).count() << " ms\n";

  // Allocate again to show reuse
  ptrs.clear();
  auto t4 = high_resolution_clock::now();
  for (int i = 0; i < N; ++i) {
    ptrs.push_back(::operator new(SMALL_SIZE));
  }
  auto t5 = high_resolution_clock::now();
  for (void* p : ptrs) ::operator delete(p);
  auto t6 = high_resolution_clock::now();

  std::cout << "Re-allocated " << N << " small blocks in "
            << duration_cast<milliseconds>(t5 - t4).count() << " ms\n";
  std::cout << "Re-deallocated " << N << " small blocks in "
            << duration_cast<milliseconds>(t6 - t5).count() << " ms\n";

  //   Large allocation(likely to trigger mmap / brk)
  std::cout << "\nBenchmark: Large allocation (may trigger mmap/brk)\n";
  auto t7 = high_resolution_clock::now();
  void* big_ptr = nullptr;
  try {
    big_ptr = ::operator new(LARGE_SIZE);
  } catch (const std::bad_alloc&) {
    std::cout << "Large allocation failed!\n";
    return -1;
  }

  size_t page_size = 4096;
  for (size_t i = 0; i < LARGE_SIZE; i += page_size) {
    static_cast<char*>(big_ptr)[i] = 1;
  }
  auto t8 = high_resolution_clock::now();
  ::operator delete(big_ptr);
  std::cout << "Allocated and touched 100MB in "
            << duration_cast<milliseconds>(t8 - t7).count() << " ms\n";

  return 0;
}