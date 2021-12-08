float distributionGGX(float NdH, float roughness) {

    float alpha = roughness * roughness;
    float a2 = alpha * alpha;
    float denom = NdH * NdH * (a2 - 1.0) + 1.0;
    denom = pi * denom * denom;
    return a2 / max(denom, 0.0000001);
}

float geometrySmith(float NdV, float NdL, float roughness) {

    float r = roughness + 1.0;
    float k = (r * r) / 8.0;

    float ggx1 = NdV / (NdV * (1.0 - k) + k);
    float ggx2 = NdL / (NdL * (1.0 - k) + k);
    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float HdV, vec3 base) {
    return base + (1.0 - base) * pow(1.0 - HdV, 5.0);
}