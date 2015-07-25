#pragma once

#include <string>

#include <GL/glew.h>

namespace fractals {

GLuint loadShaders(
    const std::string& vertexFile,
    const std::string& fragmentFile);

} // namespace fractals
