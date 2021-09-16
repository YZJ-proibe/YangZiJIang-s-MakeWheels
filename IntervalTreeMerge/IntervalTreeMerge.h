#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#define LL 1
#define RR INT_MAX

#ifndef __INTERVALTREEMERGE_H_
#define __INTERVALTREEMERGE_H_
class intervalTree;
class intervalTree {
 public:
  intervalTree()
      : _L(LL), _R(RR), _sum(0), rightSon(nullptr), leftSon(nullptr) {}
  intervalTree *_insertNewNode() { return new intervalTree(); }
  ~intervalTree() {}

  void createIntervalTree(intervalTree *intervalNode, int val, int l, int r);
  void destoryMemory();
  int querySum(intervalTree *rootTree, int queryL, int queryR);
  int lowerBoundMinAns();
  void prFirstorder(intervalTree *root);
  intervalTree *rightSon;
  intervalTree *leftSon;
  int _L, _R, _sum;
};

class mergeIntervalTree {
 public:
  mergeIntervalTree() {}
  ~mergeIntervalTree() {}
  void merge(intervalTree *rf, intervalTree *rs);
};

class _Graph {
 public:
  _Graph(int nodeHead) : _nodeHead(nodeHead) {}
  ~_Graph() {}
  void buildEdge(int _nodepre, int _nodenext);
  void dfsGraph(int nodehead, intervalTree *replaceNode);
  mergeIntervalTree *_mergeTree;
  std::vector<int> edge[100005];
  std::unordered_map<int, int> ans;
  intervalTree *_root;
  int _nodeHead;
};
#endif
