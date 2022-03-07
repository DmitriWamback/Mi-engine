#version 330 core

out vec4 fragc;

in VERTEX {
    vec3 fragp;
    vec3 normal;
    vec2 uv;
} i;

#pragma(include("pbr.glsl"))

float distributionGGX(float a, float r);
float geometrySmith(float a, float b, float r);
vec3 fresnelSchlick(float a, vec3 b);
uniform sampler2D main_tex;
uniform samplerCube skybox;
uniform vec3 camera_position;
uniform float biasOffset = 1.0;

#pragma(include("fog.glsl"))
#pragma(include("math.glsl"))

float GetDistance(vec3 fragp, vec3 cam_p, float d);
float Map(float v, float fmin, float fmax, float tmin, float tmax);
vec3 ComputeFog(float d, vec3 fogColor, vec3 fragp);

void main() {

    if (i.fragp.y < biasOffset * 15) discard;

    vec3 lightPosition = vec3(20, 12, 0);
    vec3 lightDir = normalize(lightPosition);
    vec3 nSN = normalize(i.normal);
    vec3 viewDirection  = normalize(camera_position - i.fragp);
    vec3 objectColor = texture(main_tex, i.uv / 2.0).rgb;

    float intensity = max(dot(normalize(lightDir), normalize(i.normal)), 0.2);

    vec3 halfway = normalize(lightDir + viewDirection);
    float spec = pow(max(dot(i.normal, halfway), 0.0), 1.0);
    if (intensity == 0.2) spec = 0;
    vec3 specular = vec3(1.0, 0.9, 0.6) * spec / 2.0;
    vec3 R = refract(-viewDirection, i.normal, 1.0 / 2.42);

    float fogDist = GetDistance(i.fragp, camera_position, 400.0);
    fragc = vec4(texture(skybox, R).rgb * (specular + vec3(1.0, 0.9, 0.6)/3.0 * intensity), 1.0);
    vec3 fog = ComputeFog(fogDist, vec3(1.0, 0.9, 0.6), fragc.rgb);

    if (fogDist < 1) fragc.rgb += fog;
    else fragc.rgb = fog;
}