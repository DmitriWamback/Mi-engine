#version 330 core

out vec4 fragc;

#pragma(include("debug.glsl"))
vec3 red();

void main() {
    fragc = vec4(red(), 1.0);
}