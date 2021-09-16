#include "IntervalTreeMerge.h"

int main() {
  _Graph *graph = new _Graph(5);
  int n, u, v;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> u >> v;
    graph->buildEdge(u, v);
  }
  mergeIntervalTree *_merge = new mergeIntervalTree();
  intervalTree *replace = new intervalTree();
  replace->createIntervalTree(replace, graph->_nodeHead, replace->_L,
                              replace->_R);
  graph->dfsGraph(graph->_nodeHead, replace);
  for (auto [key, keyval] : graph->ans) {
    std::cout << key << ' ' << keyval << std::endl;
  }
  return 0;
}