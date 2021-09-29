#include <iostream>
#ifndef _VECTOR_H_
#define _VECTOR_H_
class Vector;

class Vector {
 public:
  Vector() : _factor(2), _capcity(0), _size(0), isguard(0) {}
  int _size;
  int _capcity;
  int _factor;
  int isguard;
  int *_arry;

  void rebuildcapcity();
  void push_back(int val);
  void prVal();
};
#endif