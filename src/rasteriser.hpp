#pragma once

#include <string>
#include <iostream>
#include <chrono>

#include "utilities/OBJLoader.hpp"


void rasterise(Mesh mesh, std::string outputImageFile, unsigned int width, unsigned int height);
