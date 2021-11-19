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

float calculateShadow() {
    
    vec3 projectionCoords = (i.fragpl.xyz / i.fragpl.w) * 0.5 + 0.5;

    float closest = texture(depthMap, projectionCoords.st).r;
    float current = projectionCoords.z;

    float shadow = current-0.000005 > closest ? 1.0 : 0.0;

    if (projectionCoords.x > 1.0) shadow = 0.0;
    shadow = 1.0 - shadow;
    return shadow;
}

void main() {

    vec3 ambient = vec3(0.25, 0.25, 0.35);

    vec3 nDSLP  = normalize(directional_shadow_light_position);
    vec3 nSN    = normalize(i.normal);

    float dotD              = max(dot(normalize(directional_shadow_light_position - i.fragp), normalize(i.normal)), 0.25);
    float perpendicular     = dot(nDSLP, nSN);
    float n                 = max(dot(nDSLP, nSN), 0.25);

    //                        LIGHT COLOR
    vec3 diffuse = dotD * n * vec3(1.0, 1.0, 0.0) * calculateShadow();
    if (perpendicular > -0.095 && perpendicular < 0.095) diffuse = vec3(0.0);
               
    //         OBJECT COLOR
    vec3 col = vec3(1.0, 1.0, 1.0) * diffuse + ambient;
    fragc = vec4(col,1.0) * texture(main_tex, i.uv);
}