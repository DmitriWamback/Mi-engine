float GetDistance(vec3 fragp, vec3 cam_p, float maxdist) {
    return distance(fragp, cam_p) / maxdist;
}

vec3 ComputeFog(float dist, vec3 fogColor, vec3 fragc) {


    vec3 fogDifference = fogColor - fragc;
    vec3 _fogColor = dist < 1.0 ? fogDifference * dist : fogColor;
    return _fogColor;
}