#pragma once

#include <GL/glew.h>

namespace fractals {

struct Color {
    Color() = default;
    Color(GLfloat r, GLfloat g, GLfloat b);

    GLfloat r = 0.0f;
    GLfloat g = 0.0f;
    GLfloat b = 0.0f;
};

} // namespace fractals
