#version 330 core

out vec4 fragc;
uniform sampler2D _albedo0;
uniform sampler2D _albedo1;
uniform sampler2D _albedo2;
uniform float opacity;
uniform vec3 camera_position;

#INCLUDE "../../libraries/fMapping_uniforms.glsl"
#INCLUDE "../../libraries/mapping_utils.glsl"

in vec2 uv;

in VERTEX {
    vec3 normal;
    vec3 fragp;
    vec2 uv;
} i;

void main() {

    //vec2 a   = ComputeParallaxMap(_albedo2, 1.0, i.uv);
    //if (a.x > 1.0 || a.y > 1.0 || a.x < 0.0 || a.y < 0.0) discard;

    vec3 color = vec3(1.0, 0.6, 0.6);
    vec3 col = ComputeNormalMap(_albedo1, color, vec3(0.7, 0.9, 0.6), i.uv * 2.0);

    fragc = vec4(col, opacity);
}