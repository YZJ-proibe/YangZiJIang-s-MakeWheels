#include "IntervalTreeMerge.h"
void intervalTree::destoryMemory() {
  std::queue<intervalTree *> q;
  if (this != nullptr) {
    q.push(this);
  }

  while (!q.empty()) {
    auto it = q.front();
    q.pop();

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
  std::cout << "firstfor " << root->_L << ' ' << root->_R << ' ' << root->_sum
            << std::endl;
  prFirstorder(root->leftSon);
  prFirstorder(root->rightSon);
}

int intervalTree::querySum(intervalTree *rootTree, int queryL, int queryR) {
  // std::cout << rootTree->_L << ' ' << rootTree->_R << std::endl;
  if (rootTree->_L >= queryL && rootTree->_R <= queryR) {
    return rootTree->_sum;
  }
  int ans = 0;
  int MID = rootTree->_L + ((rootTree->_R - rootTree->_L) >> 1);

  if (queryL <= MID && rootTree->leftSon != nullptr) {
    ans += querySum(rootTree->leftSon, queryL, queryR);
  }
  if (queryR > MID && rootTree->rightSon != nullptr) {
    ans += querySum(rootTree->rightSon, queryL, queryR);
  }
  return ans;
}

int intervalTree::lowerBoundMinAns() {
  int L = 1, _index = 1, ans = 0;
  while (_index == this->querySum(this, 1, _index)) {
    std::cout << this->querySum(this, 1, _index) << std::endl;
    std::cout << "***" << _index << std::endl;
    _index <<= 1;
  }
  std::cout << "&&" << std::endl;
  while (L <= _index) {
    int MID = L + ((_index - L) >> 1);
    if (MID == this->querySum(this, 1, MID)) {
      ans = MID;
      L = MID + 1;
    } else {
      _index = MID - 1;
    }
  }
  return ans + 1;
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
  }

  if (rs->rightSon != nullptr) {
    if (rf->rightSon != nullptr) {
      merge(rf->rightSon, rs->rightSon);
    } else {
      rf->rightSon = new intervalTree();
      rf->rightSon = rs->rightSon;
      return;
    }
  }
}

void _Graph::buildEdge(int nodepre, int nodenext) {
  this->edge[nodepre].push_back(nodenext);
}

void _Graph::dfsGraph(int root, intervalTree *replaceNode) {
  for (int i = 0; i < edge[root].size(); i++) {
    int v = edge[root][i];
    intervalTree *tmp = new intervalTree();
    tmp->createIntervalTree(tmp, v, tmp->_L, tmp->_R);
    dfsGraph(v, tmp);
    this->_mergeTree->merge(replaceNode, tmp);
  }
  ans[root] = replaceNode->lowerBoundMinAns();
}