#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 auv;

#INCLUDE "../../libraries/vMapping_uniforms.glsl"

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 camera_position;

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

    mu.TBN = transpose(mat3(
        normalize(vec3(model * vec4(tangent,   0.0))),
        normalize(vec3(model * vec4(bitangent, 0.0))),
        normalize(vec3(model * vec4(normal,    0.0)))
    ));

    mu.t_lightp =   mu.TBN * vec3(100.0);
    mu.t_viewp  =   mu.TBN * camera_position;
    mu.t_fragp  =   mu.TBN * o.fragp;

    gl_Position = projection * view * model * vec4(position, 1.0);
}