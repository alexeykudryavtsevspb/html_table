#pragma once

#include <vector>

struct Rectangle {
  int x1 = 0;
  int y1 = 0;
  int x2 = 0;
  int y2 = 0;
};

struct Cell {
  int colspan = 1;
  int rowspan = 0;
  bool is_rect = false;
};

struct Row {
  std::vector<Cell> cells;
};

struct GeneratedLayout {
  std::vector<Row> rows;
  std::vector<int> x_coords;
  std::vector<int> y_coords;
};
