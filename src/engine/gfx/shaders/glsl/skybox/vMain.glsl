#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VERTEX {
    vec3 normal;
    vec3 tex_dir;
    vec3 fragp;
} o;

void main() {

    o.fragp = (model * vec4(vertex, 1.0)).xyz;
    o.tex_dir = normalize(normal);
    o.normal = normalize(mat3(transpose(inverse(model))) * normal);
    gl_Position = projection * view * vec4(o.fragp, 1.0);
}