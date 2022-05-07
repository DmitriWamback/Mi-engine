#define MAPPING_UNIFORM

layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

out MAPPING_UNIFORMS {
    vec3 t_lightp;
    vec3 t_viewp;
    vec3 t_fragp;
    mat3 TBN;
} mu;