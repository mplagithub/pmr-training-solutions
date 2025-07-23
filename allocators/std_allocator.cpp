#include <iostream>
#include <list>
#include <new>
#include <vector>

// Test classes
class A {
  int x;

 public:
  A() : x(1) { std::cout << "A constructed\n"; }
  ~A() { std::cout << "A destructed\n"; }
};

template <typename T>
class MyAllocator {
 public:
  using value_type = T;
  int id_ = 0;
  MyAllocator(int id) : id_(id) {}

  T* allocate(std::size_t n) {
    std::cout << "Allocating with id: " << id_ << " " << n * sizeof(T)
              << " bytes\n";
    return static_cast<T*>(::operator new(n * sizeof(T)));
  }
  void deallocate(T* p, std::size_t) {
    std::cout << "Deallocating with id: " << id_ << "\n";
    ::operator delete(p);
  }

  template <typename U>
  MyAllocator(const MyAllocator<U>& other) {}  // Rebind constructor

  // Comparison operators
  template <typename U>
  bool operator==(const MyAllocator<U>& other) const {
    return id_ == other.id_;
  }
  template <typename U>
  bool operator!=(const MyAllocator<U>& other) const {
    return !(*this == other);
  }

  // using propagate_on_container_move_assignment = std::true_type;
  using propagate_on_container_copy_assignment = std::true_type;
};

int main() {
  std::cout << "--- Allocating/Deallocating A ---\n";
  A* a = new A;
  delete a;

  // Play with std::vector<int> (insert some elements, so how allocations are
  // working)
  std::cout << "--- std::vector<int> allocation ---\n";
  std::vector<int, MyAllocator<int>> v1{MyAllocator<int>{1}};
  std::vector<int, MyAllocator<int>> v2{MyAllocator<int>{2}};
  std::list<int, MyAllocator<int>> m{MyAllocator<int>{42}};
  for (int i = 0; i < 3; ++i) {
    v1.push_back(i);
    v2.push_back(i);
  }

  std::cout << "--- std::vector<int> allocator propagation ---\n";
  v1 = std::move(v2);

  return 0;
}