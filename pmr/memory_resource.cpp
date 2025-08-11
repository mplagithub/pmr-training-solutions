#include <iostream>
#include <list>
#include <memory>
#include <memory_resource>
#include <new>
#include <vector>

class A {
  int x;

 public:
  A() : x(1) { std::cout << "A constructed\n"; }
  ~A() { std::cout << "A destructed\n"; }
};

class MyMemoryResource : public std::pmr::memory_resource {
 public:
  void* do_allocate(std::size_t bytes, std::size_t alignment) override {
    std::cout << "Allocation number " << ++counter << ", bytes: " << bytes
              << std::endl;
    return ::operator new(bytes, static_cast<std::align_val_t>(alignment));
  }

  void do_deallocate(void* p, std::size_t bytes,
                     std::size_t alignment) override {
    std::cout << "Deallocation " << p << ", bytes: " << bytes
              << ", alignment: " << alignment << std::endl;
    ::operator delete(p, bytes, static_cast<std::align_val_t>(alignment));
  }

  bool do_is_equal(const memory_resource& other) const noexcept override {
    return this == &other;
  }

 private:
  int counter{};
};

int main() {
  std::cout << "--- Allocating/Deallocating A ---\n";

  MyMemoryResource resource{};
  std::shared_ptr<A> a =
      std::allocate_shared<A>(std::pmr::polymorphic_allocator<A>(&resource));

  std::cout << "--- Allocating/Deallocating for vectors ---\n";
  std::pmr::vector<int> v1(10, &resource);
  std::pmr::vector<float> v2{&resource};
  std::pmr::list<int> l{&resource};

  for (int i = 0; i < 3; ++i) {
    v1.push_back(i);
    v2.push_back(i);
    l.push_back(i);
  }

  return 0;
}