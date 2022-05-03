#version 330 core
#extension GL_ARB_shading_language_include : require

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out VERT {
    vec3 fragp;
    vec3 normal;
    vec2 uv;
} o;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    o.fragp = (model * vec4(vertex, 1.0)).xyz;
    o.normal = normalize(mat3(transpose(inverse(model))) * normal);
    o.uv = uv;

    gl_Position = projection * view * vec4(o.fragp, 1.0);
}