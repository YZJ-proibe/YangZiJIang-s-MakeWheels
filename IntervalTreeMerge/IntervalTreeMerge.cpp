#include "IntervalTreeMerge.h"
void intervalTree::destoryMemory() {
  std::cout << "===========" << std::endl;
  std::queue<intervalTree *> q;
  // std::cout << headNode << std::endl;
  if (this != nullptr) {
    q.push(this);
  }

  while (!q.empty()) {
    auto it = q.front();
    q.pop();
    std::cout << "Destory " << (it->_L) << ' ' << (it->_R) << std::endl;
    if (it->leftSon != nullptr) {
      q.push(it->leftSon);
    }
    if (it->rightSon != nullptr) {
      q.push(it->rightSon);
    }
    delete it;
  }
}

void intervalTree::createIntervalTree(intervalTree *intervalnode, int val,
                                      int l, int r) {
  intervalnode->_L = l;
  intervalnode->_R = r;
  intervalnode->_sum++;
  std::cout << "Create " << intervalnode->_L << ' ' << intervalnode->_R
            << std::endl;
  if (l == r) {
    return;
  }
  int MID = l + ((r - l) >> 1);
  if (val <= MID) {
    intervalnode->leftSon = this->_insertNewNode();
    createIntervalTree(intervalnode->leftSon, val, l, MID);
  } else {
    intervalnode->rightSon = this->_insertNewNode();
    createIntervalTree(intervalnode->rightSon, val, MID + 1, r);
  }
}