#version 120

attribute vec3 vertexPositionModelspace;

uniform mat4 MVP;

void main() {
    gl_Position =  MVP * vec4(vertexPositionModelspace, 1.0);
}
