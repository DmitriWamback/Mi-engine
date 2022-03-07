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
uniform vec3 camera_position;

out VERTEX {
    vec3 fragp;
    vec3 normal;
    vec2 uv;
} o;

void main() {
    mat4 model = mat4(r1, r2, r3, r4);

    vec3 p = (model * vec4(position, 1.0)).xyz;
    o.fragp = p;
    o.normal = mat3(transpose(inverse(model))) * normal;
    o.uv = uv;

    float d = distance(camera_position, o.fragp)/20.0;
    vec3 pos = vec3(o.fragp.x, o.fragp.y, o.fragp.z);
    o.fragp = pos;
    gl_Position = projection * view * vec4(o.fragp, 1.0);
}