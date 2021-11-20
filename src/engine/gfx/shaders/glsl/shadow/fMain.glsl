#version 330 core
#extension GL_ARB_shading_language_include : require

out vec4 fragc;

in VERTEX {
    vec3 normal;
    vec3 fragp;
    vec2 uv;
    vec4 fragpl;
} i;
vec3 lightPosition = vec3(100.0);
uniform vec3 directional_shadow_light_position;

uniform vec3 camera_position;
uniform sampler2D depthMap;
uniform sampler2D main_tex;

#define MIN_PCF_SHADOW -2
#define MAX_PCF_SHADOW 2

float calculateShadow() {
    
    vec3 projectionCoords = (i.fragpl.xyz / i.fragpl.w) * 0.5 + 0.5;

    float closest = texture(depthMap, projectionCoords.st).r;
    float current = projectionCoords.z;


    float scale = pow(MAX_PCF_SHADOW + abs(MIN_PCF_SHADOW) + 1, 2);

    float shadow = 0;
    //shadow = current-0.000008333 > closest ? 1.0 : 0.0;
    vec2 texelSize = 1.0 / textureSize(depthMap, 0);

    for(int x = MIN_PCF_SHADOW; x <= MAX_PCF_SHADOW; ++x) {
        for (int y = MIN_PCF_SHADOW; y <= MAX_PCF_SHADOW; ++y) {
            float pcfDepth = texture(depthMap, projectionCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += current - 0.000008 > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= scale;

    if (projectionCoords.x > 1.0) shadow = 0.0;
    shadow = 1.0 - shadow;
    return shadow;
}

void main() {

    vec3 ambient = vec3(0.25, 0.25, 0.4);

    vec3 nDSLP  = normalize(directional_shadow_light_position);
    vec3 nSN    = normalize(i.normal);

    float dotD              = max(dot(normalize(directional_shadow_light_position - i.fragp), nSN), 0.0);
    float perpendicular     = dot(nDSLP, nSN);
    float n                 = max(dot(nDSLP, nSN), 0.55);
    
    float shadow = calculateShadow();
    //                        LIGHT COLOR
    vec3 diffuse = dotD * vec3(1.0, 0.8, 0.6) * shadow;
               
    //         OBJECT COLOR
    vec3 col = vec3(1.0, 1.0, 1.0) * diffuse + ambient;
    fragc = vec4(col, 1.0) * texture(main_tex, i.uv / 6.0);
}