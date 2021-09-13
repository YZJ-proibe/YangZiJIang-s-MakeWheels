#include <iostream>
#include <queue>
#define LL 1
#define RR INT_MAX
#ifndef __INTERVALTREEMERGE_H_
#define __INTERVALTREEMERGE_H_
class intervalTree;
class intervalTree {
 public:
  intervalTree()
      : isHeadNode(true), _L(LL), _R(RR), rightSon(nullptr), leftSon(nullptr) {}
  intervalTree *_insertNewNode() { return new intervalTree(); }
  ~intervalTree() {}

  void createIntervalTree(intervalTree *intervalNode, int val, int l, int r);
  void destoryMemory();
  void prFirstorder(intervalTree *root);
  intervalTree *rightSon;
  intervalTree *leftSon;
  bool isHeadNode;
  int _L, _R, _sum;
};

class mergeIntervalTree {
 public:
  int mergeNums;
  intervalTree *intervalTreeRoot;
  mergeIntervalTree(intervalTree *root) :intervalTreeRoot(root) {}
  ~mergeIntervalTree() {}
  void merge(intervalTree *rf, intervalTree *rs);
};
#endif
