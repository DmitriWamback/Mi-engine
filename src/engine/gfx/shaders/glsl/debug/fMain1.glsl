#version 330 core
#extension GL_ARB_shading_language_include : require

out vec4 fragc;

in vec3 _normal;
in vec3 fragp;
vec3 lightPosition = vec3(100.0);

uniform sampler2D depthMap;

uniform vec3 camera_position;

float calculateShadow() {
    return 0.0;
}

void main() {

    float n = exp(-max(dot(normalize(lightPosition - fragp), _normal), 0.1));
    float spec = 0.6 * pow(max(dot(normalize(camera_position - fragp), reflect(-normalize(lightPosition - fragp), _normal)), 0.0), 64);

    fragc = vec4(1.0, 0.0, 0.0, 1.0) * vec4(vec3(n) + vec3(spec), 1.0);
}