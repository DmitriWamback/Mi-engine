#version 330 core

out vec4 fragc;
uniform sampler2D _albedo0;
uniform sampler2D _albedo1;
uniform float opacity;

in vec2 uv;

in VERTEX {
    vec3 normal;
    vec3 fragp;
    vec2 uv;
} i;

void main() {
    fragc = texture(_albedo0, i.uv * 2) * texture(_albedo1, i.uv * 10);
    fragc.w = opacity;
}