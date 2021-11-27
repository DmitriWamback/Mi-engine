#version 330 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 uv;

out VERTEX {
    vec2 vertex;
    vec3 uv;
} o;

uniform vec3 position;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    vec4 screenPosition = projection * view * model * vec4(vertex, 0.0, 1.0);
    vec3 toScreen = screenPosition.xyz / screenPosition.w;
    gl_Position = vec4(toScreen, 1.0);
}