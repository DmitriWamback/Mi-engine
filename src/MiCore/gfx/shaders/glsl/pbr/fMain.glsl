#version 330 core

out vec4 fragc;

in VERT {
    vec3 fragp;
    vec3 normal;
    vec2 uv;
} i;

uniform sampler2D camera_depthTexture;
uniform sampler2D metallic;
uniform sampler2D surface;

/* INPLEMENTATION LATER */
float GGX(float NdH, float roughness) {
    
}