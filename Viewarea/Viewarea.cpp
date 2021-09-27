#include "Viewarea.h"
std::vector<int> Windows::_coordinate(4, 0);

void Windows::insertCoordinate(int x, int y, int width, int height) {
  this->_coordinate[0] = x;
  this->_coordinate[1] = y;
  this->_coordinate[2] = x + width;
  this->_coordinate[3] = y + height;
  this->_worldCoordinate.push_back(_coordinate);
}

int Windows::findWindows(int x, int y) {
  int Index = -1;
  for (int i = this->_worldCoordinate.size() - 1; i >= 0; i--) {
    if (x >= _worldCoordinate[i][0] && y >= _worldCoordinate[i][1] &&
        x <= _worldCoordinate[i][2] && y <= _worldCoordinate[i][3]) {
      return i;
    }
  }
  return Index;
}

void Windows::buildPartialData(int windowsindex) {
  int _ax = this->_worldCoordinate[windowsindex][0];
  int _ay = this->_worldCoordinate[windowsindex][1];

  int _dx = this->_worldCoordinate[windowsindex][2];
  int _dy = this->_worldCoordinate[windowsindex][3];

  int _bx = _dx;
  int _by = _ay;

  int _cx = _ax;
  int _cy = _dy;

  for (int i = windowsindex + 1; i < this->_worldCoordinate.size(); i++) {
    int ax = this->_worldCoordinate[i][0];
    int ay = this->_worldCoordinate[i][1];

    int dx = this->_worldCoordinate[i][2];
    int dy = this->_worldCoordinate[i][3];

    int bx = dx;
    int by = ay;

    int cx = ax;
    int cy = dy;

    bool isA, isB, isC, isD;
    int vertex = 0;
    isA = isB = isC = isD = false;
    if (ax >= _ax && ay >= _ay && ax <= _dx && ay <= _dy) {
      isA = true;
      vertex++;
    }

    if (bx >= _ax && by >= _ay && bx <= _dx && by <= _dy) {
      isB = true;
      vertex++;
    }

    if (cx >= _ax && cy >= _ay && cx <= _dx && cy <= _dy) {
      isC = true;
      vertex++;
    }

    if (dx >= _ax && dy >= _ay && dx <= _dx && dy <= _dy) {
      isD = true;
      vertex++;
    }

    if (!vertex) {
      continue;
    } else if (vertex == 1) {
      if (isA) {
        this->_coordinate[0] = ax;
        this->_coordinate[1] = ay;
        this->_coordinate[2] = _dx;
        this->_coordinate[3] = _dy;
      } else if (isB) {
        this->_coordinate[0] = _cx;
        this->_coordinate[1] = by;
        this->_coordinate[2] = bx;
        this->_coordinate[3] = _cy;
      } else if (isC) {
        this->_coordinate[0] = cx;
        this->_coordinate[1] = _by;
        this->_coordinate[2] = _bx;
        this->_coordinate[3] = cy;
      } else if (isD) {
        this->_coordinate[0] = _ax;
        this->_coordinate[1] = _ay;
        this->_coordinate[2] = dx;
        this->_coordinate[3] = dy;
      }
      this->_partiaMatrix.push_back(this->_coordinate);
    } else if (vertex == 2) {
      if (isA && isB) {
        this->_coordinate[0] = ax;
        this->_coordinate[1] = ay;
        this->_coordinate[2] = bx;
        this->_coordinate[3] = std::min(dy, _dy);
      } else if (isC && isD) {
        this->_coordinate[0] = cx;
        this->_coordinate[1] = std::max(ay, _ay);
        this->_coordinate[2] = dx;
        this->_coordinate[3] = dy;
      } else if (isA && isC) {
        this->_coordinate[0] = ax;
        this->_coordinate[1] = ay;
        this->_coordinate[2] = std::min(dx, _dx);
        this->_coordinate[3] = cy;
      } else if (isB && isD) {
        this->_coordinate[0] = std::max(ax, _ax);
        this->_coordinate[1] = ay;
        this->_coordinate[2] = dx;
        this->_coordinate[3] = dy;
      } else {
        this->_coordinate[0] = ax;
        this->_coordinate[1] = ay;
        this->_coordinate[2] = dx;
        this->_coordinate[3] = dy;
      }
      this->_partiaMatrix.push_back(this->_coordinate);
    } else {
      this->_coordinate[0] = ax;
      this->_coordinate[1] = ay;
      this->_coordinate[2] = dx;
      this->_coordinate[3] = dy;
      this->_partiaMatrix.push_back(this->_coordinate);
    }
  }
}

void Windows::prPartia() {
  for (auto x : this->_partiaMatrix) {
    std::cout << x[0] << ' ' << x[1] << ' ' << x[2] << ' ' << x[3] << std::endl;
  }
}

void GetFillArea::prepareData(std::vector<std::vector<int>>& matrix) {
  for (auto& Matrix : matrix) {
    Line lf(Matrix[0], Matrix[1], Matrix[3], true);
    Line ls(Matrix[2], Matrix[1], Matrix[3], false);
    this->line.push_back(lf);
    this->line.push_back(ls);
    this->_axis.push_back(Matrix[1]);
    this->_axis.push_back(Matrix[3]);
  }
  if (matrix.empty()) {
    isfill = true;
    return;
  }
  sort(line.begin(), line.end());
  sort(_axis.begin(), _axis.end());

}

void GetFillArea::pushUp(int k) {
  if (Lazy[k]) {
    Len[k] = Rson[k] - Lson[k];
  } else {
    Len[k] = Len[k << 1] + Len[k << 1 | 1];
  }
}

void GetFillArea::buildTree(int k, int Ls, int Rs) {
  Lson[k] = _axis[Ls - 1], Rson[k] = _axis[Rs - 1];
  if (Rs - Ls <= 1) {
    return;
  }
  int MID = (Ls + Rs) >> 1;
  buildTree(k << 1, Ls, MID);
  buildTree(k << 1 | 1, MID, Rs);
}

void GetFillArea::updateInterval(int k, int l, int r, int w) {
  if (Lson[k] >= l && Rson[k] <= r) {
    Lazy[k] += w;
    pushUp(k);
    return;
  }

  if (Rson[k << 1] > l) {
    updateInterval(k << 1, l, r, w);
  }

  if (Lson[k << 1 | 1] < r) {
    updateInterval(k << 1 | 1, l, r, w);
  }

  pushUp(k);
}

int GetFillArea::getFillArea() {
  int fillareas = 0;

  if (isfill) {
    return fillareas;
  }

  buildTree(1, 1, _axis.size());
  for (int i = 0; i < this->line.size() - 1; i++) {
    int pw = line[i].fla ? 1 : -1;
    updateInterval(1, line[i].ty, line[i].dy, pw);
    fillareas += Len[1] * (line[i + 1].x - line[i].x);
  }
  return fillareas;
}

int Soultion::getViewArea(std::vector<std::vector<int>>& Matrix, int x, int y) {
  std::shared_ptr<Windows> windows = std::make_shared<Windows>(Matrix.size());
  std::shared_ptr<GetFillArea> getfill = std::make_shared<GetFillArea>();
  for (auto pos : Matrix) {
    windows->insertCoordinate(pos[0], pos[1], pos[2], pos[3]);
  }
  int _index = windows->findWindows(x, y);
  int allAreas = abs(windows->_worldCoordinate[_index][0] -
                     windows->_worldCoordinate[_index][2]) *
                 abs(windows->_worldCoordinate[_index][1] -
                     windows->_worldCoordinate[_index][3]);
  windows->buildPartialData(_index);
  getfill->prepareData(windows->_partiaMatrix);
  return allAreas - getfill->getFillArea();
}