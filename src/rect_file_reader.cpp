#include "rect_file_reader.hpp"

#include <exception>
#include <fstream>

void RectFileReader::read(const std::string& input_path, std::vector<Rectangle>& out_rects) {
  std::ifstream input_file(input_path);
  if (!input_file.is_open()) {
    throw std::runtime_error("Cannot open input file.");
  }

  out_rects.clear();
  Rectangle r;
  while (input_file >> r.x1 >> r.y1 >> r.x2 >> r.y2) {
    out_rects.push_back(r);
  }
}
