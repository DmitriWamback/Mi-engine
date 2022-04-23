#version 330 core

out vec4 fragc;
uniform sampler2D test;

in vec2 uv;

in VERTEX {
    vec3 normal;
    vec3 fragp;
    vec2 uv;
} i;

void main() {
    fragc = vec4(i.normal, 1.0);
}