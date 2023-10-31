#include "../src/rb.hpp"
#include <iostream>

class Myobj {
  public:
    long long value;

    bool operator>(const Myobj& a) {
      return this->value > a.value;
    }
    bool operator<(const Myobj& a) {
      return this->value < a.value;
    }
    bool operator==(const Myobj& a) {
      return this->value == a.value;
    }
};

void test() {
  RBtree<int> rbt;

  rbt.insert(30);
  rbt.insert(1);
  rbt.insert(100);
  rbt.insert(40);

  std::cout << rbt.search(30)->value << std::endl;
  std::cout << rbt.search(42) << std::endl;
  rbt.remove(30);
  std::cout << rbt.search(30) << std::endl;
}

void test2() {
  RBtree<Myobj>* rbt = new RBtree<Myobj>();
  Myobj a, b, c;
  a.value = 24;
  b.value = 42;
  c.value = 64;

  rbt->insert(a);
  rbt->insert(b);
  std::cout << rbt->search(a) << std::endl;
  std::cout << rbt->search(b) << std::endl;
  std::cout << rbt->search(c) << std::endl;
  rbt->remove(a);
  std::cout << rbt->search(a) << std::endl;
  delete rbt;
}

int main(void) {
  test();
  system("leaks run_test");

  std::cout << "-----------------\n";
  test2();
  system("leaks run_test");

  return 0;
}
