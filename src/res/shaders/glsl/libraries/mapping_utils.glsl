#if defined(F_MAPPING_UNIFORMS)

    vec3 ComputeNormalMap(sampler2D normalmap, vec3 color, vec3 specular_color, vec2 uv) {

        vec3 normal     = normalize(texture(normalmap, uv).rgb * 2.0 - 1.0);

        vec3 lightDir   = normalize(mu.t_lightp - mu.t_fragp);
        vec3 diffuse    = max(dot(lightDir, normal), 0.2) * color;

        vec3 viewDir    = normalize(mu.t_viewp - mu.t_fragp);
        vec3 reflectDir = reflect(-lightDir, normal);
        vec3 halfway    = normalize(lightDir + viewDir);
        float spec      = pow(max(dot(normal, halfway), 0.0), 16.0);

        return diffuse + specular_color * spec;
    }

    void ComputeParallaxMap() {

    }

#endif