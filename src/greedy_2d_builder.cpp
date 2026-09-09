#include "greedy_2d_builder.hpp"

#include <algorithm>

GeneratedLayout Greedy2DTableGridBuilder::build(const std::vector<Rectangle>& rects) {
  if (rects.empty()) {
    return {};
  }

  GeneratedLayout layout;

  // Collect and sort unique coordinates
  for (const auto& r : rects) {
    layout.x_coords.push_back(r.x1);
    layout.x_coords.push_back(r.x2);
    layout.y_coords.push_back(r.y1);
    layout.y_coords.push_back(r.y2);
  }
  std::sort(layout.x_coords.begin(), layout.x_coords.end());
  layout.x_coords.erase(std::unique(layout.x_coords.begin(), layout.x_coords.end()), layout.x_coords.end());
  std::sort(layout.y_coords.begin(), layout.y_coords.end());
  layout.y_coords.erase(std::unique(layout.y_coords.begin(), layout.y_coords.end()), layout.y_coords.end());
  const std::size_t num_x = layout.x_coords.size() - 1;
  const std::size_t num_y = layout.y_coords.size() - 1;

  // Build the initial 2D cell grid
  enum class CellType { Empty, Rect, Merged };
  std::vector<std::vector<CellType>> grid(num_y, std::vector<CellType>(num_x, CellType::Empty));
  for (std::size_t y = 0; y < num_y; ++y) {
    int y_mid_2 = layout.y_coords[y] + layout.y_coords[y + 1];
    for (std::size_t x = 0; x < num_x; ++x) {
      int x_mid_2 = layout.x_coords[x] + layout.x_coords[x + 1];
      for (const auto& r : rects) {
        if (x_mid_2 >= 2 * r.x1 && x_mid_2 <= 2 * r.x2 && y_mid_2 >= 2 * r.y1 && y_mid_2 <= 2 * r.y2) {
          grid[y][x] = CellType::Rect;
          break;
        }
      }
    }
  }

  // Greedy 2D cell merging using CellType::Merged as visited marker
  layout.rows.resize(num_y);
  for (std::size_t y = 0; y < num_y; ++y) {
    for (std::size_t x = 0; x < num_x; ++x) {
      if (grid[y][x] == CellType::Merged) {
        continue;  // Skip cells already merged into earlier rowspan/colspan
      }
      const CellType target_type = grid[y][x];
      // Find maximum width (colspan)
      std::size_t max_colspan = 0;
      while (x + max_colspan < num_x && grid[y][x + max_colspan] == target_type) {
        max_colspan++;
      }
      // Find maximum height (rowspan) for the current width
      std::size_t max_rowspan = 1;
      while (y + max_rowspan < num_y) {
        bool can_expand_down = true;
        for (std::size_t c = 0; c < max_colspan; ++c) {
          if (grid[y + max_rowspan][x + c] != target_type) {
            can_expand_down = false;
            break;
          }
        }
        if (!can_expand_down) break;
        max_rowspan++;
      }
      // Mark all consumed cells as Merged
      for (std::size_t r = 0; r < max_rowspan; ++r) {
        for (std::size_t c = 0; c < max_colspan; ++c) {
          grid[y + r][x + c] = CellType::Merged;
        }
      }
      // Add the merged cell to the layout
      layout.rows[y].cells.push_back(Cell{.colspan = static_cast<int>(max_colspan),
                                          .rowspan = static_cast<int>(max_rowspan),
                                          .is_rect = (target_type == CellType::Rect)});
    }
  }

  return layout;
}
