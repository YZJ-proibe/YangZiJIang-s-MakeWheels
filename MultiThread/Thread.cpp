#include <iostream>
#include <thread>
void hello() { std::cout << "hello current world!" << std::endl; }
int main() {
  std::thread t(hello);
  std::cout << "Test order" << std::endl;

  t.join();
  return 0;
}