#version 330 core

out vec4 fragc;
in vec2 uv;
uniform sampler2D tex;

void main() {
    fragc = texture(tex, uv);
    fragc.rgb = vec3(fragc.r);
    fragc.a = fragc.r;
}