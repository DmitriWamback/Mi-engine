#version 330 core
#extension GL_ARB_shading_language_include : require

out vec4 fragc;

in VERTEX {
    vec3 normal;
    vec3 fragp;
    vec2 uv;
    vec4 fragpl;
} i;
uniform vec3 directional_shadow_light_position;

uniform vec3 camera_position;
uniform sampler2D depthMap;
uniform sampler2D main_tex;

#define MAX_PCF_SHADOW 2
#define MIN_SHADOW_BRIGHTNESS 0.00005

#define pi 3.14159265349
#define TEXTURE_SCALE 3.0

float distributionGGX(float NdH, float roughness) {

    float alpha = roughness * roughness;
    float a2 = alpha * alpha;
    float denom = NdH * NdH * (a2 - 1.0) + 1.0;
    denom = pi * denom * denom;
    return a2 / max(denom, 0.0000001);
}

float geometrySmith(float NdV, float NdL, float roughness) {

    float r = roughness + 1.0;
    float k = (r * r) / 8.0;

    float ggx1 = NdV / (NdV * (1.0 - k) + k);
    float ggx2 = NdL / (NdL * (1.0 - k) + k);
    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float HdV, vec3 base) {
    return base + (1.0 - base) * pow(1.0 - HdV, 5.0);
}

float calculateShadow() {
    
    vec3 projectionCoords = (i.fragpl.xyz / i.fragpl.w) * 0.5 + 0.5;

    float closest = texture(depthMap, projectionCoords.st).r;
    float current = projectionCoords.z;


    float scale = pow(MAX_PCF_SHADOW*2 + 1, 2);

    float shadow = 0;
    //shadow = current-0.0000008333 > closest ? 1.0 : 0.0;
    vec2 texelSize = 2.0 / textureSize(depthMap, 0);
    for(int x = -MAX_PCF_SHADOW; x <= MAX_PCF_SHADOW; ++x) {
        for (int y = -MAX_PCF_SHADOW; y <= MAX_PCF_SHADOW; ++y) {
            float pcfDepth = texture(depthMap, projectionCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += current - 0.0000008333 > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= scale;

    if (projectionCoords.z > 1.0) shadow = 0.0;
    shadow = 1.0 - shadow;    
    //shadow = max(shadow, MIN_SHADOW_BRIGHTNESS);
    return shadow;
}

void main() {


    vec3 nDSLP  = normalize(directional_shadow_light_position);
    vec3 nSN    = normalize(i.normal);
    vec3 viewDirection = normalize(camera_position - i.fragp);
    vec3 lightDirection = normalize(directional_shadow_light_position - i.fragp);

    float shadow = calculateShadow();
    float dotD = max(dot(lightDirection, nSN), 0.0);
    float n    = max(dot(nDSLP, nSN), 0.55);
    float _dotD = dot(lightDirection, nSN);

    vec4 main = texture(main_tex, i.uv / TEXTURE_SCALE);

    vec3 objectColor = main.rgb;
    vec3 lightColor = vec3(1.0, 0.9, 0.4);

    float metallic = main.r;
    float roughness = metallic / 5.0;

    vec3 reflectivity = mix(vec3(0.04), objectColor, metallic);
    vec3 col = vec3(0.0);

    vec3 shadow_ambient = vec3(0.15, 0.15, 0.35);
    vec3 halfway = normalize(viewDirection + lightDirection);
    float dist = pow(length(directional_shadow_light_position - i.fragp), 1);
    float attenuation = 1.0 / dist;

    vec3 radiance = lightColor * attenuation * 100.0;
    float NdV = max(dot(nSN, viewDirection), 0.0000001);
    float NdL = max(dot(nSN, lightDirection), 0.0000001);
    float HdV = max(dot(halfway, viewDirection), 0.0);
    float NdH = max(dot(nSN, halfway), 0.0);

    float D = distributionGGX(NdH, roughness);
    float G = geometrySmith(NdV, NdL, roughness);
    vec3 F = fresnelSchlick(HdV, reflectivity);

    vec3 specular = D * G * F;
    specular /= 1.0 * NdV * NdL;
    vec3 kD = vec3(1.0) - F;
    kD *= 1.0 - metallic;

    float inverse_shadow = 1 - shadow;
    
    col += (kD * objectColor / pi + specular) * radiance * NdL;
    col = col / (col + vec3(1.0));
    col = pow(col, vec3(1.0 / 5.2));
    col *= max(shadow * dotD, MIN_SHADOW_BRIGHTNESS);
    col += main.rgb * min((1 - (shadow * _dotD)), 0.1);

    vec3 diffuse = dotD * lightColor * shadow;
    fragc = vec4(col + (main.rgb / 5.0), 1.0);
}