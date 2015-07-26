#pragma once

#include "Model.hpp"

class GLFWwindow;

namespace fractals {

class Sierpinski {
public:
    Sierpinski() = default;
    ~Sierpinski();

    void run();
private:
    bool init();

    Model model;
    GLFWwindow* window = nullptr;
};

} // namespace fractals
