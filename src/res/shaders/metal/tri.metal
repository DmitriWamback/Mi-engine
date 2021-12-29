#include <metal_stdlib>
using namespace metal;

struct Vertex {
    vector_float3 position;
    vector_float3 normal;
};

struct vOut {
    float4 position [[position]];
    float4 fragp;
    float3 normal;
};

struct Uniforms {
    float4x4 projection;
    float4x4 view;
    float4x4 model;
};

vertex vOut vertMain(const device Vertex *arr [[buffer(0)]], 
                  unsigned int vid [[vertex_id]], 
                  constant Uniforms &u [[buffer(1)]]) {

    Vertex i = arr[vid];
    vOut o;
    o.position = u.projection * u.view * u.model * i.position;
    o.fragp = (u.model * float4(i.position, 1.0)).xyz;
    o.normal = (u.model * float4(i.normal, 1.0)).xyz;

    return o;
}

fragment float4 fragMain(vOut i [[stage_in]]) {
    return float4(1.0);
}