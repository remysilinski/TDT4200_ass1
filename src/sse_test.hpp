#pragma once
#include "utilities/OBJLoader.hpp"
#include <vector>

union sse_float4 {
    // Task 3.b) addition of a float4
    float4 f4vector;
    float __attribute__ ((vector_size (16))) vector;
    float elements[4];
};

void sse_test(Mesh &);
