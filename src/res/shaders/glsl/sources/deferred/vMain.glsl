#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VERTEX {
    vec3 fragp;
    vec3 normal;
    vec2 uv;
} o;

void main() {
    o.normal = normalize(mat3(transpose(inverse(model))) * normal);
    o.fragp = (model * vec4(position, 1.0)).xyz;
    o.uv = uv;

    gl_Position = projection * view * model * vec4(position, 1.0);
}