#pragma once

#include "types.hpp"

#include <string>
#include <vector>

class RectFileReader {
 public:
  static void read(const std::string& input_path, std::vector<Rectangle>& out_rects);
};
