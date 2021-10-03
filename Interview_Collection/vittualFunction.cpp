#include <iostream>
#include <memory>

int main() {
  int a = 1, b = 2;
  std::min(a, b);
  std::cout << a << ' ' << b << std::endl;
  return 0;
}