#version 330 core

out vec4 fragc;

in VERTEX {
    vec3 fragp;
    vec3 normal;
    vec2 uv;
} i;
uniform sampler2D img;

void main() {

    vec4 a = texture(img, i.uv);
    if (a.a < 0.5) discard;

    vec4 col = vec4(vec3((a.r + a.g + a.b)/3.0) * vec3(1.0, 0.6, 0.6), 1.0);
    fragc = col;
}