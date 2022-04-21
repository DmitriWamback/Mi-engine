#version 330 core

out vec4 fragc;
uniform sampler2D test;

in vec2 uv;

void main() {
    fragc = vec4(0.6, 0.7, 0.5, 1.0) * texture(test, uv);
}