#include <algorithm>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#ifndef _VIEWARE_H_
#define _VIEWARE_H_
#define L INT_MIN
#define R INT_MAX
class Windows;
class Line;
class GetFillArea;
class Soultion;

class Windows {
 public:
  Windows() {}
  Windows(int windowsNums)
      : _windowsSize(windowsNums), _worldHeight(100), _worldWidth(100) {
    _worldIndex.first = _worldIndex.second = 0;
  }
  ~Windows() {}
  int _windowsSize;
  int _worldHeight;
  int _worldWidth;
  static std::vector<int> _coordinate;
  std::pair<int, int> _worldIndex;                 //世界坐标原点
  std::vector<std::vector<int>> _worldCoordinate;  //世界坐标点
  void setWindowsSize(int size) { this->_windowsSize = size; }
  void setWorldHeight(int heigth) { this->_worldHeight = heigth; }
  void setWorldWidth(int width) { this->_worldWidth = width; }
  void insertCoordinate(int x, int y, int width, int height);
  int findWindows(int x, int y);
  void buildPartialData(int windowsIndex);  //构造局部矩形内的数据
  void prPartia();
  std::vector<std::vector<int>> _partiaMatrix;
};

class Line {
 public:
  Line(int sx, int sty, int sdy, bool sfla)
      : x(sx), ty(sty), dy(sdy), fla(sfla) {}
  int x, ty, dy;
  bool fla;
  bool operator<(const Line& a) { return x < a.x; }
};

class GetFillArea {
 public:
  GetFillArea() {}
  std::unordered_map<int, int> Len, Lazy, Rson, Lson;
  std::vector<Line> line;
  std::vector<int> _axis;
  void prepareData(std::vector<std::vector<int>>& matrix);
  void buildTree(int k, int Ls, int Rs);
  void updateInterval(int k, int l, int r, int w);
  void pushUp(int k);
  int getFillArea();
  bool isfill = false;
};

class Soultion {
 public:
  Soultion(){};
  int getViewArea(std::vector<std::vector<int>>& Matrix,int x,int y);
};
#endif