#version 330 core

layout (location = 0) out vec4 _albedo;
layout (location = 1) out vec4 _normal;
layout (location = 2) out vec4 _position;

in VERTEX {
    vec3 fragp;
    vec3 normal;
    vec2 uv;
} i;

uniform sampler2D tex;
uniform bool has_tex = false;
uniform vec3 color = vec3(1.0);

uniform float farplane;
uniform vec3 camera_position;

void main() {

    if (has_tex) _albedo = vec4(color, 1.0);
    else _albedo = vec4(color, 1.0);

    _normal = vec4(i.normal, 1.0);
    _position = vec4(i.fragp, 1.0);
}