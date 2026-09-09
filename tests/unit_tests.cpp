#include "greedy_2d_builder.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

// Grid-based Layout Verifier
// Verifies layout structure against exact coordinate compression grid.
class LayoutVerifier {
 public:
  static void verify(const std::vector<Rectangle>& input_rects, const GeneratedLayout& layout) {
    if (input_rects.size() == 0) {
      assert(layout.rows.size() == 0);
      assert(layout.x_coords.size() == 0);
      assert(layout.y_coords.size() == 0);
      return;
    }

    auto [expected_x, expected_y] = build_expected_grid(input_rects);

    assert(layout.x_coords == expected_x);
    assert(layout.y_coords == expected_y);

    const std::size_t num_x = expected_x.size() - 1;
    const std::size_t num_y = expected_y.size() - 1;

    enum class CellType { None, Rect, Void };
    std::vector<std::vector<CellType>> actual_grid(num_y, std::vector<CellType>(num_x, CellType::None));

    // Populate layout into grid
    for (std::size_t r = 0; r < layout.rows.size(); ++r) {
      std::size_t cell_idx = 0;
      std::size_t c = 0;

      while (c < num_x) {
        // Skip columns already covered by rowspan from upper rows
        if (actual_grid[r][c] != CellType::None) {
          c++;
          continue;
        }

        assert(cell_idx < layout.rows[r].cells.size());
        const auto& cell = layout.rows[r].cells[cell_idx];

        const CellType type = cell.is_rect ? CellType::Rect : CellType::Void;

        // Mark grid region
        for (int rr = 0; rr < cell.rowspan; ++rr) {
          for (int cc = 0; cc < cell.colspan; ++cc) {
            assert(r + rr < num_y);
            assert(c + cc < num_x);

            // Overlap check: cell must be strictly unvisited
            assert(actual_grid[r + rr][c + cc] == CellType::None);

            actual_grid[r + rr][c + cc] = type;
          }
        }

        c += cell.colspan;
        cell_idx++;
      }
      assert(cell_idx == layout.rows[r].cells.size());
    }

    // Verify exact geometry matching
    for (std::size_t r = 0; r < num_y; ++r) {
      for (std::size_t c = 0; c < num_x; ++c) {
        const int x1 = expected_x[c];
        const int x2 = expected_x[c + 1];
        const int y1 = expected_y[r];
        const int y2 = expected_y[r + 1];

        const bool expected_rect = is_inside_any_rect(x1, y1, x2, y2, input_rects);
        const CellType expected_type = expected_rect ? CellType::Rect : CellType::Void;

        assert(actual_grid[r][c] == expected_type);
      }
    }
  }

 private:
  static std::pair<std::vector<int>, std::vector<int>> build_expected_grid(const std::vector<Rectangle>& input_rects) {
    std::vector<int> x_coords;
    std::vector<int> y_coords;
    for (const auto& r : input_rects) {
      x_coords.push_back(r.x1);
      x_coords.push_back(r.x2);
      y_coords.push_back(r.y1);
      y_coords.push_back(r.y2);
    }
    std::sort(x_coords.begin(), x_coords.end());
    x_coords.erase(std::unique(x_coords.begin(), x_coords.end()), x_coords.end());
    std::sort(y_coords.begin(), y_coords.end());
    y_coords.erase(std::unique(y_coords.begin(), y_coords.end()), y_coords.end());
    return {x_coords, y_coords};
  }

  static bool is_inside_any_rect(int x1, int y1, int x2, int y2, const std::vector<Rectangle>& rects) {
    const int cx = x1 + (x2 - x1) / 2;
    const int cy = y1 + (y2 - y1) / 2;
    for (const auto& r : rects) {
      if (r.x1 <= cx && cx <= r.x2 && r.y1 <= cy && cy <= r.y2) {
        return true;
      }
    }
    return false;
  }
};

// --------------------------------------------------------------------------------------------------------------------------
void run_layout_test(const std::string& test_name, const std::vector<Rectangle>& rects) {
  Greedy2DTableGridBuilder builder;
  GeneratedLayout layout = builder.build(rects);

  LayoutVerifier verifier;
  verifier.verify(rects, layout);

  std::cout << "[PASSED] " << test_name << std::endl;
}

// --------------------------------------------------------------------------------------------------------------------------
void test_single_rectangle() {
  // single rectangle spanning a sub-region of the grid
  run_layout_test("test_single_rectangle", {{100, 100, 500, 500}});
}

void test_empty() {
  // empty
  run_layout_test("test_empty", {});
}

void test_full_screen_rectangle() {
  // single rectangle occupying the entire 1000x1000 area without gaps
  run_layout_test("test_full_screen_rectangle", {{0, 0, 1000, 1000}});
}

void test_basic_two_rectangles() {
  // two non-overlapping diagonal rectangles with empty space between them
  run_layout_test("test_basic_two_rectangles", {{0, 0, 100, 100}, {200, 200, 300, 300}});
}

void test_touching_rectangles() {
  // two rectangles sharing a common border along the X axis
  run_layout_test("test_touching_rectangles", {{0, 0, 100, 100}, {100, 0, 200, 100}});
}

void test_corner_rectangles() {
  // four rectangles placed in four corners of the grid
  run_layout_test("test_corner_rectangles",
                  {{0, 0, 100, 100}, {900, 0, 1000, 100}, {0, 900, 100, 1000}, {900, 900, 1000, 1000}});
}

void test_u_shaped_voids() {
  // three rectangles forming a U-shape around a central empty space
  run_layout_test("test_u_shaped_voids", {{0, 0, 100, 300}, {0, 200, 300, 300}, {200, 0, 300, 300}});
}

// --------------------------------------------------------------------------------------------------------------------------
int main() {
  std::cout << "Running unit tests..." << std::endl;

  test_single_rectangle();
  test_empty();
  test_full_screen_rectangle();
  test_basic_two_rectangles();
  test_touching_rectangles();
  test_corner_rectangles();
  test_u_shaped_voids();

  std::cout << "All unit tests passed successfully!" << std::endl;
  return 0;
}
