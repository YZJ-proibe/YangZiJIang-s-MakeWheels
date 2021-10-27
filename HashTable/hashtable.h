#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_
#include <iostream>
#include <list>
#include <memory>
#include <queue>

/*元素节点类*/
class Node {
 public:
  Node(int key = 0, int val = 0, bool isexit = false)
      : _key(key), _val(val), _isExit(isexit) {}
  int _key, _val;
  bool _isExit;
};

class HashTable {
 public:
  /*构造函数*/
  HashTable();
  /*找到val的key值*/
  int find(int val);
  /*插入数据*/
  void insert(int x);
  /*删除元素*/
  void erase(int x);
  /*获取元素*/
  int getval(int key);
  /*获取元素个数*/
  int getsize();
  /*获取内存长度*/
  int getcapcity();

 private:
  /*存放数据的容器*/
  Node* _arry;
  /*容器中元素数量*/
  int _size;
  /*容器内存*/
  int _capcity;
  /*平衡因子*/
  float _factor;
  /*扩容因子*/
  int _expansionFactor;
  /*检查是否可以进行扩容*/
  bool isExpansion();
  /*自动扩容*/
  void AutoExpansion();
  /*重新分配内存后需要重新hash*/
  Node ReHash(Node& _arry1);
  /*释放内存*/
  void ReaseMemory(Node* tmp);
  /*哈希函数1*/
  int Hash1(int val);
  /*哈希函数2*/
  int Hash2(int val);
  /*哈希函数3*/
  int Hash3(int val);
  /*真正使用的哈希函数*/
  int Hash(int val);
};
#endif