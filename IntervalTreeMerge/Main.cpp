#include "IntervalTreeMerge.h"
int main() {
  intervalTree *it = new intervalTree();
  intervalTree *ita = new intervalTree();
  intervalTree *itt = new intervalTree();
  mergeIntervalTree *its = new mergeIntervalTree(it);
  it->createIntervalTree(it, 1, it->_L, it->_R);
  ita->createIntervalTree(ita, 2, ita->_L, ita->_R);
  itt->createIntervalTree(itt, 5, itt->_L, itt->_R);
  its->merge(its->intervalTreeRoot, ita);
  its->intervalTreeRoot->prFirstorder(its->intervalTreeRoot);
  std::cout << "^^^" << std::endl;
  its->merge(its->intervalTreeRoot, itt);
  its->intervalTreeRoot->prFirstorder(its->intervalTreeRoot);
  return 0;
}