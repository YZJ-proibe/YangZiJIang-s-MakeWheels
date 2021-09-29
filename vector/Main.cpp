#include "Vector.h"
int main() {
  Vector vec;
  for (int i = 0; i < 1000000; i++) {
    vec.push_back(i);
  }
  std::cout << vec.isguard << std::endl;
  // vec.prVal();
}