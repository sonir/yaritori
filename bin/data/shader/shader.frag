#version 150

uniform float color;
out vec4 outputColor;

void main() {
    outputColor = vec4(color, color, color, 1.0);
}
