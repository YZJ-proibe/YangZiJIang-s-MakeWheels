#include "Vector.h"
void Vector::rebuildcapcity() {
  int n = (_capcity == 0) ? 1 : _capcity;
  this->isguard++;
  int *_tmp = new int[n << 1];
  for (int i = 0; i < n; i++) {
    _tmp[i] = _arry[i];
  }
  _capcity = n << 1;
  delete[] _arry;
  _arry = _tmp;
}

void Vector::push_back(int val) {
  if (_size == _capcity) {
    rebuildcapcity();
  }
  ++_size;
  _arry[_size - 1] = val;
}

void Vector::prVal() {
  for (int i = 0; i < _size; i++) {
    std::cout << _arry[i] << std::endl;
  }
}