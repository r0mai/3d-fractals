#include "Shader.hpp"

#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

namespace fractals {

namespace {

std::string readStream(std::istream& stream) {
    return {std::istreambuf_iterator<char>(stream), {}};
}

std::string readFile(const std::string& fileName) {
    std::ifstream stream(fileName);
    if (!stream) {
        return "";
    }
    return readStream(stream);
}

bool compileShader(GLuint shaderId, const std::string& code) {
    auto codePtr = code.c_str();
    glShaderSource(shaderId, 1, &codePtr, NULL);
    glCompileShader(shaderId);

    GLint result = GL_FALSE;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

    if (!result) {
        GLint logLength = -1;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> errorMessage(std::max(logLength, 1));
        glGetShaderInfoLog(shaderId, logLength, nullptr, errorMessage.data());
        std::cerr << "Shader compilation failed: " <<
            std::string(errorMessage.begin(), errorMessage.end()) << std::endl;
        return false;
    }
    return true;
}

bool linkShader(GLuint vertexId, GLuint fragmentId, GLuint& programId) {
    programId = glCreateProgram();
    glAttachShader(programId, vertexId);
    glAttachShader(programId, fragmentId);
    glLinkProgram(programId);

    GLint result = GL_FALSE;

    // Check the program
    glGetProgramiv(programId, GL_LINK_STATUS, &result);

    if (!result) {
        GLint logLength = -1;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> errorMessage(std::max(logLength, 1));
        glGetProgramInfoLog(programId, logLength, nullptr, errorMessage.data());
        std::cerr << "Shader linking failed: " <<
            std::string(errorMessage.begin(), errorMessage.end()) << std::endl;
        return false;
    }
    return true;
}

} // anonymous namespace

GLuint loadShaders(
    const std::string& vertexFile,
    const std::string& fragmentFile)
{
    GLuint vertexId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentId = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertexCode = readFile(vertexFile);
    std::string fragmentCode = readFile(fragmentFile);

    compileShader(vertexId, vertexCode);
    compileShader(fragmentId, fragmentCode);

    GLuint programId = 0;
    linkShader(vertexId, fragmentId, programId);

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);

    return programId;
}

} // namespace fractals
