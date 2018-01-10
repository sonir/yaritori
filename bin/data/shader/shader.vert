#version 150

in vec4 position;
uniform mat4 modelViewProjectionMatrix;

uniform float t;

void main() {
    vec4 pos = modelViewProjectionMatrix * position;
    pos.x += sin(t) * 5;
    pos.y += cos(t) * 5;
    gl_Position = pos;

}
