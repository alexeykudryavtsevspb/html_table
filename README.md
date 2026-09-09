# HTML Table Grid Builder

C++20 tool that converts input rectangles coordinates into a structured HTML table layout without gaps and overlaps using a 2D greedy merging algorithm.

## Requirements

* C++20 compatible compiler (GCC or Clang)
* CMake 3.15+
* Python 3 (optional, for sample generation)

## Project Structure

* `src/` - Core library and main application logic.
* `tests/` - Unit tests suite.
* `samples/` - Sample input files and rendered HTML results.
* `gensample.py` - Script to generate random input rectangles.

## Quick Start

### 1. Build and Run Sample
```bash
make run
```

### 2. Run Unit Tests
```bash
make test
```

### 3. Generate New Sample Data
```bash
make gensample
```

### 4. Custom Usage
```bash
./build/html_table path/to/input.txt path/to/output.html
```

## Key Features

* **No Absolute Positioning**: Relies strictly on standard HTML table geometry (`<tr>`, `<td>`, `colspan`, `rowspan`, `<colgroup>`) without absolute CSS positioning.
* **Standard Dependencies**: Built using standard C++20 and STL libraries without external heavy frameworks.
* **Compact Output**: Minimizes HTML size by combining grid coordinates and omitting redundant inline styles.

## Specifications & Assumptions

* **Interval Representation**: Each rectangle covers half-open intervals `[x1, x2) × [y1, y2)`.
* **Coordinate System**: Origin `(0,0)` is at the top-left corner. The X-axis goes right, and the Y-axis goes down.
* **Pixel Mapping**: Coordinates map directly as `1 unit = 1 CSS pixel` within a standard `0..1000` range.
* **Colors**: Table background is white; rectangles are rendered with green background (`#4CAF50`).
* **Compact HTML**: Generated table uses direct `<col>` widths, `rowspan`, and `colspan` without redundant wrapper tags to minimize HTML size.
* **Input Validity**: Input data is assumed to be valid and non-overlapping.

## Input File Format

The input file (e.g., `samples/sample.txt`) contains a list of non-overlapping rectangles. 
Each line defines one rectangle using four space-separated integer coordinates:

```text
x1 y1 x2 y2
```

Where:

* `x1, y1` - Top-left corner coordinates (`x1 < x2`).
* `x2, y2` - Bottom-right corner coordinates (`y1 < y2`).

### Example
```text
0 0 100 100
200 200 300 300
```
