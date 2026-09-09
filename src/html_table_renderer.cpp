#include "html_table_renderer.hpp"

#include <exception>
#include <format>
#include <fstream>

bool HtmlTableRenderer::render(const std::string& output_path, const GeneratedLayout& layout) {
  std::ofstream out(output_path);
  if (!out.is_open()) {
    throw std::runtime_error("Cannot open output file.");
  }

  out << "<style>\n";
  out << "table{border-collapse:collapse;table-layout:fixed;margin:0;padding:0}\n";
  out << "td{padding:0;overflow:hidden}\n";
  out << ".rect{background:#4CAF50}\n";
  out << "</style>\n";
  out << "<table>\n";

  out << "<colgroup>";
  for (std::size_t i = 0; i + 1 < layout.x_coords.size(); ++i) {
    const int col_width = layout.x_coords[i + 1] - layout.x_coords[i];
    out << std::format("<col style=width:{}px>", col_width);
  }
  out << "\n";

  for (std::size_t i = 0; i < layout.rows.size() && i + 1 < layout.y_coords.size(); ++i) {
    const auto& row = layout.rows[i];
    const int row_height = layout.y_coords[i + 1] - layout.y_coords[i];
    out << std::format("<tr style=height:{}px>", row_height);
    for (const auto& cell : row.cells) {
      out << "<td";
      if (cell.is_rect) {
        out << " class=rect";
      }
      if (cell.colspan > 1) {
        out << std::format(" colspan={}", cell.colspan);
      }
      if (cell.rowspan > 1) {
        out << std::format(" rowspan={}", cell.rowspan);
      }
      out << ">";
    }
    out << '\n';
  }

  return true;
}
