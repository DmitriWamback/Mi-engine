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
    fragc = vec4(1.0, 1.0, 1.0, 1.0) * texture(img, i.uv);
}