#version 330 core

out vec4 fragc;

in VERTEX {
    vec3 fragp;
    vec3 normal;
    vec2 uv;
} i;

void main() {
    vec3 lightDir = normalize(vec3(300, 542, 10));
    vec3 col = vec3(1.0, 0.0, 0.0) * max(dot(i.normal, lightDir), 0.5);

    fragc = vec4(col, 1.0);
}