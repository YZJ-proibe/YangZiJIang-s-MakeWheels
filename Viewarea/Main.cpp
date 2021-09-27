#include <iostream>
#include <memory>

#include "Viewarea.h"

int main() {
  std::shared_ptr<Soultion> soultion = std::make_shared<Soultion>();
  /*测试数据*/
  std::vector<std::vector<int>> Matrix = {{1, 1, 3, 3}, {1, 1, 1, 1},
                                          {1, 3, 1, 2}, {3, 2, 2, 2},
                                          {4, 4, 2, 2}, {2, 2, 5, 5}};
  /*光标所在位置*/
  int gx, gy;
  gx = 4, gy = 1;

  std::cout << "ViewArea: " << soultion->getViewArea(Matrix, gx, gy) << std::endl;

  return 0;
}