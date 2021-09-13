#include "IntervalTreeMerge.h"
int main() {
  intervalTree *it =new intervalTree();
  it->createIntervalTree(it, 1, it->_L, it->_R);

  it->destoryMemory();

  return 0;
}