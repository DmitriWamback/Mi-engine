# shaderC creates a shader for any graphics api supported by the Mi Engine

SHADERTYPE=$1
SHADERNAME=$2

if [ $SHADERTYPE == "--help" ]
then
    echo "cmd <type> <name>"
    echo "--o [TYPE] creates an OpenGL compatible GLSL shader"
    echo "--v [TYPE] creates a Vulkan compatible GLSL shader"
    echo "--m [TYPE] creates a Metal compatible metal shader"
fi

if [ $SHADERTYPE == "--o" ] 
then
    cd src/res/shaders/glsl
    mkdir $SHADERNAME
    cd $SHADERNAME
    touch vMain.glsl
    touch fMain.glsl

    echo "#version 330 core
          
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VERTEX {
    vec3 fragp;
    vec3 normal;
    vec2 uv;
} o;

void main() {
    o.fragp = (model * vec4(position, 1.0)).xyz;
    o.normal = normalize(normal);
    o.uv = uv;

    gl_Position = projection * view * vec4(o.fragp, 1.0);
}
" >> vMain.glsl

    echo "#version 330 core

out vec4 fragc;

in VERTEX {
    vec3 fragp;
    vec3 normal;
    vec2 uv;
} i;

uniform vec3 albedo;
uniform sampler2D main_tex;

void main() {
    fragc = vec4(texture(main_tex, i.uv).rgb * albedo, 1.0);
}
" >> fMain.glsl
fi