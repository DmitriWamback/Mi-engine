#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 _normal;
out vec3 fragp;

void main() {
    fragp = (model * vec4(position, 1.0)).xyz;
    _normal = normalize(mat3(transpose(inverse(model))) * normal);
    gl_Position = projection * view * model * vec4(position, 1.0);
}