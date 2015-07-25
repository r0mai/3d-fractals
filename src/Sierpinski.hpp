#pragma once

class GLFWwindow;

namespace fractals {

class Sierpinski {
public:
    Sierpinski() = default;
    ~Sierpinski();

    void run();
private:
    bool init();

    GLFWwindow* window = nullptr;
};

} // namespace fractals
