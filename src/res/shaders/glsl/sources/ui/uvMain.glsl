#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

out VERTEX {
    vec2 uv;
} o;

void main() {
    o.uv = uv;
    gl_Position = vec4(position, 0.0, 1.0);
}