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
    vec3 lightColor = vec3(1.0, 0.9, 0.4);

    float metallic = objectColor.r * 3;
    float roughness = (1 - metallic) / 4.0;
    vec3 reflectivity = mix(vec3(0.1), objectColor, metallic);
    vec3 col = vec3(0.0);

    vec3 shadow_ambient = vec3(0.15, 0.15, 0.35);
    vec3 halfway = normalize(viewDirection + lightDir);
    float dist = pow(length(lightPosition - i.fragp), 1);
    float attenuation = 1.0 / dist;

    vec3 radiance = lightColor * attenuation * 100.0;
    float NdV = max(dot(nSN, viewDirection), 0.0000001);
    float NdL = max(dot(nSN, lightDir), 0.0000001);
    float HdV = max(dot(halfway, viewDirection), 0.0);
    float NdH = max(dot(nSN, halfway), 0.0);

    float D = distributionGGX(NdH, roughness);
    float G = geometrySmith(NdV, NdL, roughness);
    vec3 F = fresnelSchlick(HdV, reflectivity);

    vec3 specular = D * G * F;
    specular /= 1.0 * NdV * NdL;
    vec3 kD = vec3(1.0) - F;
    kD *= 1.0 - metallic;
    float pi = 3.14159265359;
    col += (kD * objectColor / pi + specular) * radiance * NdL;
    col = col / (col + vec3(1.0));
    col = pow(col, vec3(1.0 / 5.2));

    fragc = vec4(col + (objectColor / 5.0), 1.0);
}