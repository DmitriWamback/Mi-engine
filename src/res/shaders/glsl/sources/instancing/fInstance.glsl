#version 330 core

out vec4 fragc;

in VERTEX {
    vec3 fragp;
    vec3 normal;
    vec2 uv;
} i;
void main() {

    fragc = vec4(1.0, 1.0, 1.0, 1.0);
}