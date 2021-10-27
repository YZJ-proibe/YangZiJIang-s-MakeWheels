#include "hashtable.h"

/*私有成员*/

HashTable::HashTable() {
  _size = 0;
  _capcity = 10;
  _factor = 0.7;
  _arry = new Node[_capcity];
  _expansionFactor = 2;
}

bool HashTable::isExpansion() {
  float xs = 1.0 * _size / _capcity;
  return xs >= _factor;
}

Node HashTable::ReHash(Node& _arry1) {
  Node node(0, 0, false);
  node._val = _arry1._val;
  node._key = Hash(node._val);
  node._isExit = true;
  return node;
}

void HashTable::AutoExpansion() {
  int Len = _capcity;
  _capcity *= _expansionFactor;
  Node* arry = new Node[_capcity];
  Node* tmp = _arry;
  _arry = arry;
  for (int i = 0; i < Len; i++) {
    if (tmp[i]._isExit) {
      auto node = ReHash(tmp[i]);
      arry[node._key] = node;
    }
  }
  ReaseMemory(tmp);
}

void HashTable::ReaseMemory(Node* tmp) {
  delete[] tmp;
}

int HashTable::Hash1(int val) {
  int times = 3;
  int k = 1;
  while (times--) {
    val = (val + k * k + _capcity) % _capcity;
    k++;
  }
  return val;
}

int HashTable::Hash2(int val) {
  int times = 2;
  while (times--) {
    val = (val + 1 + _capcity) % _capcity;
  }
  return val;
}

int HashTable::Hash3(int val) {
  int times = 4;
  while (times--) {
    val = (val + times * 51 + _capcity) % _capcity;
  }
  return val;
}

int HashTable::Hash(int val) {
  int nowval = val;
  do {
    val = Hash1(Hash2(Hash3(val)));
  } while (_arry[val]._isExit && (nowval != _arry[val]._val));
  return val;
}

/*共有成员*/

void HashTable::insert(int val) {
  Node node(0, 0, false);
  node._key = Hash(val);
  if (_arry[node._key]._isExit) {
    return;
  }
  node._val = val;
  node._isExit = true;
  _arry[node._key] = node;
  _size++;
  if (isExpansion()) {
    AutoExpansion();
  }
}

int HashTable::find(int val) {
  int key = Hash(val);
  return _arry[key]._isExit ? key : -1;
}

int HashTable::getval(int key) {
  return _arry[key]._val;
}

int HashTable::getsize() {
  return _size;
}

int HashTable::getcapcity() {
  return _capcity;
}

void HashTable::erase(int x) {
  int key = find(x);
  _arry[key] = Node{0, 0, false};
  _size--;
}
