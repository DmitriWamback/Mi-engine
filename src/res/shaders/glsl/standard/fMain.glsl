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
    fragc = vec4(vec3(102, 153, 0)/255.0, 1.0);
}