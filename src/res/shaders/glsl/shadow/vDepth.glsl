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

    if (isInstanced == 0)
        gl_Position = lightSpaceMatrix_projection * lightSpaceMatrix_view * model * vec4(position, 1.0);

    else if (isInstanced == 1) {
        mat4 m = mat4(r1, r2, r3, r4);
        gl_Position = lightSpaceMatrix_projection * lightSpaceMatrix_view * m * vec4(position, 1.0);
    }
}