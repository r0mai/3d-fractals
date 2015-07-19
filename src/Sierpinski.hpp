#pragma once

class GLFWwindow;

namespace fractals {

class Sierpinski {
public:

    ~Sierpinski();

    void run();
private:
    bool init();

    GLFWwindow* window = nullptr;
};

} // namespace fractals
