#include <iostream>
#include <new>
#include <vector>

// Test classes
class A {
  int x;

 public:
  A() : x(1) { std::cout << "A constructed\n"; }
  ~A() { std::cout << "A destructed\n"; }
};

class MyAllocator {
 public:
  void* allocate(std::size_t size) {
    std::cout << "[MyAllocator] Allocated " << size << " bytes at "
              << static_cast<void*>(buffer + offset) << std::endl;
    offset += size;
    return buffer + offset - size;
  }

  void deallocate(void* ptr) {
    std::cout << "[MyAllocator] Deleting memory at " << ptr << std::endl;
  }

 private:
  int offset = 0;
  static unsigned char buffer[256];
};

unsigned char MyAllocator::buffer[256] = {0};

MyAllocator alloc;

void* operator new(std::size_t size) {
  void* ptr = alloc.allocate(size);
  if (!ptr) throw std::bad_alloc();
  return ptr;
}
void operator delete(void* ptr) noexcept { alloc.deallocate(ptr); }

int main() {
  std::cout << "--- Allocating/Deallocating A ---\n";
  A* a = new A;
  delete a;

  std::cout << "--- std::vector<int> allocation ---\n";
  std::vector<int> v;
  for (int i = 0; i < 3; ++i) v.push_back(i);

  return 0;
}