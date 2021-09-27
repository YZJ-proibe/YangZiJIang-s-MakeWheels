#include <iostream>
#include <memory>

#include "Viewarea.h"

int main() {
  std::shared_ptr<Windows> windows = std::make_shared<Windows>();
  std::shared_ptr<GetFillArea> r = std::make_shared<GetFillArea>();
  windows->setWindowsSize(5);

  windows->insertCoordinate(1, 1, 3, 3);

  windows->insertCoordinate(1, 1, 1, 1);

  windows->insertCoordinate(1, 3, 1, 2);
  windows->insertCoordinate(3, 2, 2, 2);
  windows->insertCoordinate(1, 1, 3, 3);

  int index = windows->findWindows(1, 1);

  windows->buildPartialData(index);

  r->prepareData(windows->_partiaMatrix);
  std::cout << r->getFillArea() << std::endl;

  return 0;
}