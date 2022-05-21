#version 330 core

layout(location = 0) in vec4 in_attr;

out vec2 uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {

    uv = in_attr.zw;
    gl_Position = vec4(in_attr.xy, 0.0, 1.0);
}