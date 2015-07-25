#version 120

attribute vec3 vertexPositionModelspace;

void main() {
    gl_Position = vec4(vertexPositionModelspace, 1.0);
}
