#version 330 core

out vec4 fragc;

in VERTEX {
    vec3 fragp;
    vec3 normal;
    vec2 uv;
} i;

#pragma(include("pbr.glsl"))

float distributionGGX(float a, float r);
float geometrySmith(float a, float b, float r);
vec3 fresnelSchlick(float a, vec3 b);
uniform sampler2D main_tex;
uniform vec3 camera_position;

void main() {

    vec3 lightPosition = vec3(0, 132, 0);
    vec3 lightDir = normalize(lightPosition - i.fragp);
    vec3 nSN = normalize(i.normal);
    vec3 viewDirection  = normalize(camera_position - i.fragp);
    vec3 objectColor = texture(main_tex, i.uv / 2.0).rgb;

    float intensity = (dot(normalize(lightPosition - i.fragp), normalize(i.normal)) + 1.0) / 4.0 + 0.5;

    if (objectColor == vec3(0.0))
        fragc = vec4(1.0, 0.0, 0.0, 1.0) * intensity/2.0;
    else
        fragc = vec4(objectColor, 1.0) * intensity / 2.0;
}