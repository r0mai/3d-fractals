#include "Sierpinski.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

namespace fractals {

bool Sierpinski::init() {
    if (!glfwInit()) {
        std::cerr << "Can't init glfw" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);

    if (!window) {
        std::cerr << "Can't open glfw window" << std::endl;
        return false;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Can't init glew" << std::endl;
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return true;
}

Sierpinski::~Sierpinski() {
    glfwTerminate();
}

void Sierpinski::run() {
    init();
    do {
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0 );
}

} // namespace fractals
