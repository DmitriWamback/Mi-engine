float calculateShadow(sampler2D depthMap, vec3 normal, vec4 fragpl, vec3 lightPosition, vec3 fragp, float cameraFarPlane) {

    vec4 projectionCoords = (fragpl.xyzw) * 0.5 + 0.5;

    float closest = texture(depthMap, projectionCoords.st).r;
    float current = projectionCoords.z;

    float shadow = 0;

    float p = dot(normal, normalize(lightPosition - fragp));
    
    // BIAS = 0.005 ÷ CAMERA ZFAR
    float bias = 0.06*0.39 / cameraFarPlane;
    float a_bias = max(bias * (1.0 - p), bias);
    float b_bias = max(bias * (1.0 - p), bias);
    shadow = current-bias > closest ? 1.0 : 0.0;

    if (projectionCoords.z > 1.0) shadow = 0.0;
    shadow = 1.0 - shadow;
    return shadow;
}