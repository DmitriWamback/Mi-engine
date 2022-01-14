float CalculateShadow(sampler2D depthMap, vec3 normal, vec4 fragpl, vec3 lightPosition, vec3 fragp, float cameraFarPlane) {

    vec4 projectionCoords = (fragpl.xyzw) * 0.5 + 0.5;

    float closest = texture(depthMap, projectionCoords.st).r;
    float current = projectionCoords.z;

    float shadow = 0;

    float p = dot(normal, normalize(lightPosition - fragp));
    
    // BIAS = 0.005 ÷ CAMERA ZFAR
    float bias = 0.06*0.39 / cameraFarPlane;
    float a_bias = max(bias * (1.0 - p), bias);
    float b_bias = max(bias * (1.0 - p), bias);
    shadow = current-a_bias > closest ? 1.0 : 0.0;

    if (projectionCoords.z > 1.0) shadow = 0.0;
    shadow = 1.0 - shadow;
    return shadow;
}

float CalculatePCFShadows(sampler2D depthMap, vec4 fragpl, vec3 fragp, float cameraFarPlane, int halfKernalWidth, vec3 normal, vec3 lightPosition) {

    vec4 projectionCoords = (fragpl.xyzw) * 0.5 + 0.5;

    float p = dot(normal, normalize(lightPosition - fragp));
    float bias = 0.06*0.39 / cameraFarPlane;
    float a_bias = max(bias * (1.0 - p), bias);
    float closest = texture(depthMap, projectionCoords.st).r;
    float current = projectionCoords.z - a_bias;

    int isInShadows = current > closest ? 1 : 0;

    float shadow = 0.0;
    int scale = (halfKernalWidth * 2 + 1) * (halfKernalWidth * 2 + 1);

    vec2 texel = 1.0 / textureSize(depthMap, 0);

    if (isInShadows == 1) {
        shadow = -halfKernalWidth;
        for (int x = -halfKernalWidth; x <= halfKernalWidth; x++) {
            for (int y = -halfKernalWidth; y <= halfKernalWidth; y++) {
                float depth = texture(depthMap, projectionCoords.st + vec2(x, y) * texel).r;
                shadow += current > depth ? 1.0 : -0.5;
            }
        }
    }

    if (shadow == scale) {
        shadow /= scale;
    }
    else {
        shadow /= scale;
    }
    return 1.0 - shadow;
}   