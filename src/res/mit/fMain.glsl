#version 330 core

out vec4 fragc;
in vec3 color;

void main() {
    fragc = vec4(color, 1.0);
}