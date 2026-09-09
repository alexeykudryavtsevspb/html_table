#pragma once

#include "types.hpp"

#include <vector>

class ITableGridBuilder {
 public:
  virtual ~ITableGridBuilder() = default;

  virtual GeneratedLayout build(const std::vector<Rectangle>& rects) = 0;
};
