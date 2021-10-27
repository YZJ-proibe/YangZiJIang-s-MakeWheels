#include <time.h>
#include <algorithm>
#include <vector>
#include "hashtable.h"
int main() {
  HashTable test;
  std::vector<int> v(1000000, 0);
  std::vector<int> _Ms(1000000, 0);
  for (int i = 0; i < 1000000; i++) {
    // v[i] = rand();
    test.insert(i);
  }
  for (int i = 0; i < 1000000; i++) {
    int start = clock();
    int a = test.find(i);
    int end = clock();
    _Ms[i] = end - start;
    if (test.getval(a) != i) {
      puts("-1");
    }
  }

  std::sort(_Ms.begin(), _Ms.end());
  std::cout << _Ms[_Ms.size() - 1] << std::endl;
  std::cout << test.getsize() << std::endl;
  test.erase(5);
  std::cout << test.find(5) << std::endl;
  std::cout << test.getsize() << std::endl;

  return 0;
}