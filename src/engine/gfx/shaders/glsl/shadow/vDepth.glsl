#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 lightSpaceMatrix_projection;
uniform mat4 lightSpaceMatrix_view;
uniform mat4 model;

void main() {
    gl_Position = lightSpaceMatrix_projection * lightSpaceMatrix_view * model * vec4(position, 1.0);
}