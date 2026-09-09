#pragma once

#include "i_table_grid_builder.hpp"

class Greedy2DTableGridBuilder : public ITableGridBuilder {
 public:
  GeneratedLayout build(const std::vector<Rectangle>& rects) override;
};
