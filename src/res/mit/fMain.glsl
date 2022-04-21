#version 330 core

out vec4 fragc;
in vec3 color;
in vec3 pos;

void main() {

    float dir = distance(pos, vec3(0.0))/100.0;
    fragc = vec4(color * dir * vec3(1.0, 0.6, 0.9), 1.0);
}