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
uniform bool has_tex;
uniform vec3 color;

void main() {

    if (has_tex) _albedo = texture(tex, i.uv);
    else _albedo = vec4(color, 1.0);

    _normal = i.normal;
    _position = i.position;
}