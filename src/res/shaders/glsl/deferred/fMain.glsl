#version 330 core

layout (location = 0) out vec4 _albedo;
layout (location = 1) out vec4 _normal;
layout (location = 2) out vec4 _position;
layout (location = 3) out vec4 _depth;

in VERTEX {
    vec3 fragp;
    vec3 normal;
    vec2 uv;
} i;

uniform sampler2D tex;
uniform bool has_tex = false;
uniform vec3 color;

uniform float farplane;
uniform vec3 camera_position;

void main() {

    if (has_tex) _albedo = texture(tex, i.uv);
    else _albedo = vec4(color, 1.0);

    _normal.xyz = i.normal;
    _position.xyz = i.fragp;

    _depth = vec4(distance(camera_position, i.fragp) / farplane, 0.0, 0.0, 1.0);
}