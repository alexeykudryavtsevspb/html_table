#include "greedy_2d_builder.hpp"
#include "html_table_renderer.hpp"
#include "rect_file_reader.hpp"

#include <format>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  int exit_code = 1;
  try {
    const std::string input_path = (argc > 1) ? argv[1] : "sample.txt";
    const std::string output_path = (argc > 2) ? argv[2] : "sample.html";
    std::cout << "Input path: " << input_path << std::endl;

    std::vector<Rectangle> rects;
    RectFileReader reader;
    reader.read(input_path, rects);

    Greedy2DTableGridBuilder builder;
    GeneratedLayout layout = builder.build(rects);

    HtmlTableRenderer renderer;
    renderer.render(output_path, layout);

    std::cout << "Done. Output path: " << output_path << std::endl;
    exit_code = 0;
  } catch (const std::exception& ex) {
    std::cerr << "Error: " << ex.what() << '\n';
  } catch (...) {
    std::cerr << "Error: unknown exception\n";
  }

  return exit_code;
}
