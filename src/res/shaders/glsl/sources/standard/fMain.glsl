#version 330 core

out vec4 fragc;
uniform sampler2D _albedo0;
uniform sampler2D _albedo1;
uniform sampler2D _albedo2;
uniform sampler2D _albedo3;
uniform float opacity;
uniform vec3 camera_position;

uniform mat4 lightSpaceMatrix_projection;
uniform mat4 lightSpaceMatrix_view;

#INCLUDE "../../libraries/fMapping_uniforms.glsl"
#INCLUDE "../../libraries/mapping_utils.glsl"
#INCLUDE "../../libraries/directional_shadow.glsl"

in vec2 uv;

in VERTEX {
    vec3 normal;
    vec3 fragp;
    vec2 uv;
} i;

void main() {

    float shadow = CalculateShadow(_albedo3, i.normal, (lightSpaceMatrix_projection * lightSpaceMatrix_view * vec4(i.fragp, 1.0)), vec3(-100.0), i.fragp, 10000.0);

    //vec2 a   = ComputeParallaxMap(_albedo2, 1.0, i.uv);
    //if (a.x > 1.0 || a.y > 1.0 || a.x < 0.0 || a.y < 0.0) discard;

    vec3 color = vec3(1.0, 0.6, 0.6);
    vec3 shadow_ambient = vec3(0.15, 0.15, 0.35);
    float diff = max(dot(i.normal, normalize(vec3(100))), 0.0);
    vec3 diffuse = color * diff + shadow_ambient * (1 - diff);
    vec3 col = ComputeNormalMap(_albedo1, color, vec3(0.7, 0.9, 0.6), i.uv * 10.0);
    
    //fragc = vec4(diffuse * (1 - shadow), 1.0);
    fragc = vec4(color * shadow + ((vec3(0.15, 0.15, 0.35) + color)/2) * (1 - shadow), 1.0);
    //fragc.rgb *= texture(_albedo0, i.uv * 32).rgb;
}