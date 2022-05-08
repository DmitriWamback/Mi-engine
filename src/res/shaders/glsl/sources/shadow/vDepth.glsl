#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

layout (location = 3) in vec4 r1;
layout (location = 4) in vec4 r2;
layout (location = 5) in vec4 r3;
layout (location = 6) in vec4 r4;

uniform mat4 lightSpaceMatrix_projection;
uniform mat4 lightSpaceMatrix_view;
uniform mat4 model;

uniform int isInstanced;

void main() {
    gl_Position = lightSpaceMatrix_projection * lightSpaceMatrix_view * model * vec4(position, 1.0);
}