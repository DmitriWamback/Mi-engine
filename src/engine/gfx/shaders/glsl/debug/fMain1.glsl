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

    float dotD = dot(normalize(directional_shadow_light_position - i.fragp), normalize(i.normal));
    float n    = dot(normalize(directional_shadow_light_position), normalize(i.normal));

    vec3 a = normalize(cross(normalize(i.normal), normalize(directional_shadow_light_position - i.fragp)));
    
    vec3 diffuse = dotD * vec3(1.0, 0.0, 0.0) * calculateShadow();

    vec3 col = vec3(1.0, 0.0, 0.0) * diffuse + ambient;
    fragc = vec4(col,1.0) * texture(main_tex, i.uv);
}