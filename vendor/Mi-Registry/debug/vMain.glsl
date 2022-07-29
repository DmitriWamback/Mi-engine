#version 330 core

layout(location = 0) in vec4 in_attr;

out vec2 uv;

void main() {

    uv = in_attr.zw;
    gl_Position = vec4(in_attr.xy, 0.0, 1.0);
}