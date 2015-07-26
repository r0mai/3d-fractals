#version 120

attribute vec3 vertexPositionModelspace;
attribute vec3 vertexColor;

varying vec3 fragmentColor;

uniform mat4 MVP;

void main() {
    gl_Position =  MVP * vec4(vertexPositionModelspace, 1.0);

    fragmentColor = vertexColor;
}
