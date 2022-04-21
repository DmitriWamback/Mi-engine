#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in float weight;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 color;
out vec3 pos;

void main() {
    pos = position;
    gl_PointSize = 10.0;
    gl_Position = projection * view * vec4(position, 1.0);
    color = vec3(weight);
}