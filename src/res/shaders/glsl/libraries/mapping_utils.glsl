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

    vec2 ComputeParallaxMap(sampler2D depthMap, float height_scale, vec2 uv) {

        const float minLayers = 8;
        const float maxLayers = 32;

        vec3 viewDir = normalize(mu.t_viewp - mu.t_fragp);
        vec2 p = viewDir.xy / viewDir.z * height_scale;
        float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));
        float layerDepth = 1.0 / numLayers;
        float currentLayerDepth = 0.0;

        vec2 initial = uv;
        float height = texture(depthMap, initial).r;
        while (currentLayerDepth < height) {
            initial -= (p / numLayers);
            height = texture(depthMap, initial).r;
            currentLayerDepth += layerDepth;
        }

        return initial;
    }

    bool isEdge(vec2 uv) {
        return (uv.x > 1.0 || uv.y > 1.0 || uv.x < 0.0 || uv.y < 1.0);
    }

#endif