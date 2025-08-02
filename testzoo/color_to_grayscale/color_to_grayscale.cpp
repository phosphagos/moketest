#include "moketest/common.hpp"
#include "color_to_grayscale.hpp"
#include <cstdio>

static int TestSuitIndex = 0;

void ExecuteColorToGrayscale(size_t height, size_t width) {
    println("========= Test Suit {} =========", TestSuitIndex++);
    println("Basic Info:");
    println("       height: {}", height);
    println("        width: {}", width);
    ColorToGrayscaleExecutor{height, width, 300, 500}.execute();
}

int main() {
    ExecuteColorToGrayscale(62, 761);
    ExecuteColorToGrayscale(1024, 2048);
    ExecuteColorToGrayscale(1500, 2000);
}
