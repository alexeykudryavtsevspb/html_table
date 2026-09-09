#pragma once

#include "types.hpp"

#include <string>

class HtmlTableRenderer {
 public:
  bool render(const std::string& output_path, const GeneratedLayout& layout);
};
