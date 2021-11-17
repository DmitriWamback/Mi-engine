#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix_projection;
uniform mat4 lightSpaceMatrix_view;

out VERTEX {
    vec3 normal;
    vec3 fragp;
    vec2 uv;
    vec4 fragpl;
} o;

void main() {
    o.fragp = (model * vec4(position, 1.0)).xyz;
    o.normal = normalize(mat3(transpose(inverse(model))) * normal);
    o.uv = uv;
    o.fragpl = lightSpaceMatrix_projection * lightSpaceMatrix_view * vec4(o.fragp, 1.0);
    gl_Position = projection * view * model * vec4(position, 1.0);
}