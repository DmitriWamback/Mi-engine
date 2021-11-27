#version 330 core
#define DIRECTIONAL_SHADOWS_IMPLEMENTATION

float isInShadow(sampler2D depthMap, vec4 fragp_lightSpace, vec3 normal, vec3 lightDirection) {

    vec3 projectionCoords = (fragp_lightSpace.xyz / fragp_lightSpace.w) * 0.5 + 0.5;
    float closest = texture(depthMap, projectionCoords.st).r;
    float current = projectionCoords.z;

    float bias = max(0.05 * (1.0 - dot(normal, lightDirection)), 0.005);
    float shadow = current - bias > closest ? 1.0 : 0.0;

    if (projectionCoords.z > 1.0) shadow = 0.0;
    return shadow;
}