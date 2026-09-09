BUILD_DIR ?= build
MAIN_EXE := $(BUILD_DIR)/html_table
TEST_EXE := $(BUILD_DIR)/unit_tests

.PHONY: all build test run clean clangformat

all: build

build:
	@cmake -B $(BUILD_DIR) -S .
	@cmake --build $(BUILD_DIR)

test: build
	@./$(TEST_EXE)

run: build
	@./$(MAIN_EXE) samples/sample.txt samples/sample.html

clean:
	@rm -rf $(BUILD_DIR)

clangformat:
	clang-format -i src/* tests/*

gensample:
	cd samples && python3 gensample.py
