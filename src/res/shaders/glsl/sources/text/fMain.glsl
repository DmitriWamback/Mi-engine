#version 330 core

out vec4 fragc;
in vec2 uv;
uniform sampler2D tex;

void main() {

    float o = texture(tex, uv).r;
    if (o < 0.6) discard;

    fragc = vec4(vec3(1.0), o);
}