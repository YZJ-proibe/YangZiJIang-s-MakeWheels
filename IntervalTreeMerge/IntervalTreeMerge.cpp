#include "IntervalTreeMerge.h"
void intervalTree::destoryMemory() {
  std::queue<intervalTree *> q;
  if (this != nullptr) {
    q.push(this);
  }

  while (!q.empty()) {
    auto it = q.front();
    q.pop();
    // std::cout << "Destory " << (it->_L) << ' ' << (it->_R) << std::endl;
    if (it->leftSon != nullptr) {
      q.push(it->leftSon);
    }
    if (it->rightSon != nullptr) {
      q.push(it->rightSon);
    }
    std::cout << "===========" << std::endl;
    delete it;
  }
}

void intervalTree::createIntervalTree(intervalTree *intervalnode, int val,
                                      int l, int r) {
  intervalnode->_L = l;
  intervalnode->_R = r;
  intervalnode->_sum++;
  // std::cout << "Create " << intervalnode->_L << ' ' << intervalnode->_R
  //<< std::endl;
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
void intervalTree::prFirstorder(intervalTree *root) {
  if (root == nullptr) {
    return;
  }
  std::cout << "firstfor " << root->_L << ' ' << root->_R << std::endl;
  prFirstorder(root->leftSon);
  prFirstorder(root->rightSon);
}
void mergeIntervalTree::merge(intervalTree *rf, intervalTree *rs) {
  rf->_sum += rs->_sum;
  if (rs->leftSon != nullptr) {
    if (rf->leftSon != nullptr) {
      merge(rf->leftSon, rs->leftSon);
    } else {
      rf->leftSon = new intervalTree();
      rf->leftSon = rs->leftSon;
      return;
    }
  } else {
    if (rf->rightSon != nullptr) {
      merge(rf->rightSon, rs->rightSon);
    } else {
      rf->rightSon = new intervalTree();
      rf->rightSon = rs->rightSon;
      return;
    }
  }
}