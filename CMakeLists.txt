cmake_minimum_required(VERSION 3.16)
project(HtmlTable CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic -Werror -O3 -march=native -flto)
add_link_options(-flto)

include_directories(src)

add_library(html_table_core STATIC
    src/types.hpp
    src/rect_file_reader.cpp
    src/rect_file_reader.hpp
    src/html_table_renderer.cpp
    src/html_table_renderer.hpp
    src/i_table_grid_builder.hpp
    src/greedy_2d_builder.cpp
    src/greedy_2d_builder.hpp
)

add_executable(html_table src/main.cpp)
target_link_libraries(html_table PRIVATE html_table_core)

add_executable(unit_tests tests/unit_tests.cpp)
target_link_libraries(unit_tests PRIVATE html_table_core)
