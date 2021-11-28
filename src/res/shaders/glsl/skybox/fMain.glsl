#version 330 core

out vec4 fragc;

in VERTEX {
    vec3 normal;
    vec3 tex_dir;
    vec3 fragp;
} i;

uniform samplerCube cubemap;

void main() {
    fragc = texture(cubemap, i.tex_dir);
}
