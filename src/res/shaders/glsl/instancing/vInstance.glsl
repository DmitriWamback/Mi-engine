#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

// Instancing
layout (location = 3) in vec4 r1;
layout (location = 4) in vec4 r2;
layout (location = 5) in vec4 r3;
layout (location = 6) in vec4 r4;

// uniforms
uniform mat4 projection;
uniform mat4 view;

out VERTEX {
    vec3 fragp;
    vec3 normal;
    vec2 uv;
} o;

void main() {
    mat4 model = mat4(r1, r2, r3, r4);
    o.fragp = (model * vec4(position, 1.0)).xyz;
    o.normal = mat3(transpose(inverse(model)));
    o.uv = uv;

    gl_Position = projection * view * model;
}