#include "Sierpinski.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "Shader.hpp"

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

    const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    // This will identify our vertex buffer
    GLuint vertexbuffer;

    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);

    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    // Give our vertices to OpenGL.
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(g_vertex_buffer_data),
        g_vertex_buffer_data,
        GL_STATIC_DRAW);

	GLuint programId = loadShaders("shaders/simple.vert", "shaders/simple.frag");

    do {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programId);

        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
           0,                  // attribute 0.
           3,                  // size
           GL_FLOAT,           // type
           GL_FALSE,           // normalized?
           0,                  // stride
           (void*)0            // array buffer offset
        );

        // Draw the triangle !
        // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0 );
}

} // namespace fractals
