#include "Sierpinski.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

    const GLfloat vertexBuffer[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    // This will identify our vertex buffer
    GLuint vertexBufferHandle;

    // Generate 1 buffer, put the resulting identifier in vertexBufferHandle
    glGenBuffers(1, &vertexBufferHandle);

    // The following commands will talk about our 'vertexBufferHandle' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);

    GLuint programId = loadShaders("shaders/simple.vert", "shaders/simple.frag");

    GLuint matrixId = glGetUniformLocation(programId, "MVP");

    // Get a handle for our buffers
    GLuint vertexPositionModelspaceID = glGetAttribLocation(
        programId, "vertexPositionModelspace");

    glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

    glm::mat4 view = glm::lookAt(
        glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 MVP = projection * view * model;

    // Give our vertices to OpenGL.
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertexBuffer),
        vertexBuffer,
        GL_STATIC_DRAW);


    do {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programId);

        glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);

        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(vertexPositionModelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
        glVertexAttribPointer(
            vertexPositionModelspaceID,
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // Draw the triangle !
        // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(vertexPositionModelspaceID);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0 );

    glDeleteBuffers(1, &vertexBufferHandle);
    glDeleteProgram(programId);
}

} // namespace fractals
