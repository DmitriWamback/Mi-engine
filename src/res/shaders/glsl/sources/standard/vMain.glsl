#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 auv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 uv;

out VERTEX {
    vec3 normal;
    vec3 fragp;
    vec2 uv;
} o;

void main() {
    uv = auv;

    o.normal = normal;
    o.fragp = (model * vec4(position, 1.0)).xyz;
    o.uv = auv;
    gl_Position = projection * view * model * vec4(position, 1.0);
}