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

class B {
  int y, z;

 public:
  B() : y(2), z(3) { std::cout << "B constructed\n"; }
  ~B() { std::cout << "B destructed\n"; }
};

// 1. Overload global operator new/delete here (print pointer and size)
void* operator new(std::size_t size) {
  void* ptr = std::malloc(size);
  std::cout << "[global new overload] Allocated  " << size << " bytes at "
            << ptr << std::endl;
  if (!ptr) throw std::bad_alloc();
  return ptr;
}
void operator delete(void* ptr) noexcept {
  std::cout << "[global delete overload] Deleting memory at " << ptr
            << std::endl;
  std::free(ptr);
}

// 2. Declare static buffer for C here
static unsigned char c_buffer[8];

class C {
  int a, b;

 public:
  C() : a(4), b(5) { std::cout << "C constructed\n"; }
  ~C() { std::cout << "C destructed\n"; }

  // 3. Overload operator new/delete just for class C (print pointer and size)
  void* operator new(std::size_t size) {
    void* ptr = std::malloc(size);
    std::cout << "[C::new overload] Allocated  " << size << " bytes at " << ptr
              << std::endl;
    if (!ptr) throw std::bad_alloc();
    return ptr;
  }
  void operator delete(void* ptr) noexcept {
    std::cout << "[C::delete overload] Deleting memory at " << ptr << std::endl;
    std::free(ptr);
  }
  // 4. Placement new using static buffer (print pointer)
  void* operator new(std::size_t size, unsigned char* buffer) {
    std::cout << "[C::placement new] Using static buffer at "
              << static_cast<void*>(buffer) << std::endl;
    return buffer;
  }
  void operator delete(void* ptr, unsigned char* buffer) noexcept {
    std::cout << "[C::placement delete] (no real deallocation needed) at "
              << ptr << std::endl;
  }
};

int main() {
  // 5. Allocate and delete A, B, C
  std::cout << "--- Allocating/Deallocating A ---\n";
  A* a = new A;
  delete a;

  std::cout << "--- Allocating/Deallocating B ---\n";
  B* b = new B;
  delete b;

  std::cout << "--- Allocating/Deallocating C (class-specific new) ---\n";
  C* c1 = new C;
  delete c1;

  std::cout << "--- Allocating/Deallocating C with placement new (static "
               "buffer) ---\n";
  C* c2 = new (c_buffer) C;
  c2->~C();  // Manual destructor call, no delete needed

  // 6. Play with std::vector<int> (insert some elements, so how allocations are
  // working)
  std::cout << "--- std::vector<int> allocation ---\n";
  std::vector<int> v;
  for (int i = 0; i < 10; ++i) v.push_back(i);

  return 0;
}