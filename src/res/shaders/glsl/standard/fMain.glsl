#version 330 core

out vec4 fragc;
uniform sampler2D _albedo0;

in vec2 uv;

in VERTEX {
    vec3 normal;
    vec3 fragp;
    vec2 uv;
} i;

void main() {
    fragc = texture(_albedo0, i.uv * 10);
}