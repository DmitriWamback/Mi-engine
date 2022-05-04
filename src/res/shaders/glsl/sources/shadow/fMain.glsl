#version 330 core

out vec4 fragc;

in VERTEX {
    vec3 originNormal;
    vec3 normal;
    vec3 fragp;
    vec2 uv;
    vec4 fragpl;
} i;
uniform vec3 directional_shadow_light_position;

uniform vec3 camera_position;
uniform vec3 mouse_ray;
uniform sampler2D depthMap;
uniform sampler2D _albedo0;

#define MAX_PCF_SHADOW 4
#define MIN_SHADOW_BRIGHTNESS 0.2

uniform float biasOffset = 1.0;
uniform float opacity;
uniform float sCameraFarPlane;
uniform samplerCube skybox;

#define TEXTURE_SCALE 2.0

// INCLDUING FILES
#INCLUDE "../../libraries/pbr.glsl"
#INCLUDE "../../libraries/directional_shadow.glsl"
#INCLUDE "../../libraries/perlin_noise.glsl"
#INCLUDE "../../libraries/fog.glsl"
#INCLUDE "../../libraries/math.glsl"

float noise_layer(vec3 p, float persistance, float lacunarity, int octaves, float freq, float ampl) {

    float n;
    float f = freq;
    float a = ampl;

    for (int i = 0; i < octaves; i++) {
        n += noise((p.x) * f, (p.y) * f, (p.z) * f) * a;
        f *= lacunarity;
        a *= persistance;
    }

    return n;
}


void main() {

    vec3 nDSLP  = normalize(directional_shadow_light_position);
    vec3 nSN    = normalize(i.normal);
    vec3 viewDirection  = normalize(camera_position - i.fragp);
    vec3 lightDirection = normalize(directional_shadow_light_position);

    float shadow = 0;

    shadow = CalculateShadow(depthMap,
                             i.normal,
                             i.fragpl,
                             directional_shadow_light_position,
                             i.fragp,
                             sCameraFarPlane);
    
    float dotD = max(dot(lightDirection, nSN), 0.0);
    float n    = max(dot(nDSLP, nSN), 0.55);
    float _dotD = dot(lightDirection, nSN);
    vec4 main = texture(_albedo0, i.uv / TEXTURE_SCALE);

    //float noiseIntensity = Map(noise_layer(i.fragp, 0.5, 2.0, 4, 3.0, 1.0), -1.0, 1.0, 0.1, 0.3);
    vec3 objectColor = main.rgb;
    vec3 lightColor = vec3(1.0, 0.9, 0.4);

    float metallic = objectColor.r;
    float roughness = (1 - metallic) / 4.0;

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

    vec3 R = refract(-viewDirection, i.originNormal, 1.0 / 1.52);
    float reflectionIntensity = pow(0.9, 1.0);

    float shadowIntensity = shadow * dotD;
    
    float pi = 3.14159265349;
    col += (kD * objectColor / pi + specular) * radiance * NdL;
    col = col / (col + vec3(1.0));
    col = pow(col, vec3(1.0 / 5.2));
    col *= shadowIntensity;
    col = objectColor * min((1 - (shadow * dotD)), MIN_SHADOW_BRIGHTNESS);

    vec3 diffuse = dotD * lightColor * shadow;
    fragc = vec4(col + (objectColor / 2.0), 1.0) + texture(skybox, R) * reflectionIntensity * shadowIntensity;

    float fdist = GetDistance(i.fragp, camera_position, 50.0);
    vec3 fog = ComputeFog(fdist, vec3(1.0, 0.9, 0.8), fragc.rgb);

    if (fdist < 1)
        fragc.rgb += fog;
    else
        fragc.rgb = fog;

    fragc.w = opacity;

    // VISUALIZE MOUSE RAY
    // fragc.rgb += vec3(1.0, 0.0, 0.0) * max(dot(-normalize(camera_position - i.fragp), mouse_ray), 0.0);

    // VISUALIZE NORMALS
    fragc.rgb = abs(normalize(i.normal));
}