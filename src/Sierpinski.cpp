#include "Sierpinski.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

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
        return false;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    model = Model::createPyramid(
        glm::vec3(1, 0, -1),
        glm::vec3(-1, 0, -1),
        glm::vec3(0, 0, 1),
        glm::vec3(0, 1, 0)
    );

    return true;
}

Sierpinski::~Sierpinski() {
    glfwTerminate();
}

void Sierpinski::run() {
    init();

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
        glm::vec3(3, 0.5, 3), // Camera location
        glm::vec3(0, 0, 0), // Where to look
        glm::vec3(0, 1, 0)  // Up vector
    );

    model.setTransform(glm::mat4(1.0f));

    do {
        auto vertexBuffer = model.toVertexBuffer();
        // Give our vertices to OpenGL.
        glBufferData(
            GL_ARRAY_BUFFER,
            vertexBuffer.size() * sizeof(GLfloat),
            vertexBuffer.data(),
            GL_STATIC_DRAW);

        glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

        glm::mat4 view = glm::lookAt(
            glm::vec3(0, 0, 5), // Camera is at (4,3,3), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
        );

        auto rotateMatrix = glm::rotate(1.0f, glm::vec3(0.0, 1.0, 0.0));
        model.setTransform(model.getTransform() * rotateMatrix);

        glm::mat4 MVP = projection * view * model.getTransform();

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

        glDrawArrays(GL_TRIANGLES, 0, model.getTriangleCount() * 3);

        glDisableVertexAttribArray(vertexPositionModelspaceID);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0);

    glDeleteBuffers(1, &vertexBufferHandle);
    glDeleteProgram(programId);
}

} // namespace fractals
