/* Including required libraries */
/* C++ built-in libraries */
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>

/* 3rd Party libraries */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/* Custom libraries */
#include "engine/extern.h"
// MATH
#include "math/vector.h"
#include "math/matrix.h"
#include "math/noise.h"
// ENGINE
#include "engine/engine.h"

/* Main method */

mi_inheritable::Scene scene1 = mi_inheritable::Scene("hello");

#define DEBUG_SEED 14121.40
#define s 40

#define FREQ 19.2

float get_noise_density_at(int x, int y, int z, float seed) {
    float xNoise, yNoise, zNoise;
    xNoise = mi::noise(y/FREQ, z/FREQ, seed);
    yNoise = mi::noise(x/FREQ, z/FREQ, seed);
    zNoise = mi::noise(x/FREQ, y/FREQ, seed);

    return xNoise + yNoise + zNoise;
}

int main() {
    __engineBegin();

    renderbuf cbuffer = renderbuf();
    renderbuf mesh_buf = renderbuf();
    mi::Mesh mesh = mi::Mesh(mesh_buf);

    /* SHADER DEFINITIONS HERE */
    Shader shadowShader("shadow/vMain.glsl", "shadow/fMain.glsl", "SHADOW SHADER");
    Shader debugShader2("debug/vMain.glsl", "debug/fMain1.glsl", "RED");
    MI_addShader(shadowShader);
    MI_addShader(debugShader2);

    mi::StaticCamera shadowCamera = mi::StaticCamera(mi::STATICCAMERAPROPERTIES_ORTHOGRAPHIC(), "DEPTH TEXTURE");

    float seed = rand() % 100000;
    //seed = 32193;
    float CUBE_SIZE = 0.5;
    float _density = 0.5;

    std::cout << seed << std::endl;

    for (int x = 0; x < s; x++) {
        for (int y = 0; y < s; y++) {
            for (int z = 0; z < s; z++) {
                
                float density = get_noise_density_at(x, y, z, seed);
                float up    = get_noise_density_at(x, y+1, z, seed);
                float down  = get_noise_density_at(x, y-1, z, seed);
                float left  = get_noise_density_at(x-1, y, z, seed);
                float right = get_noise_density_at(x+1, y, z, seed);
                float front = get_noise_density_at(x, y, z-1, seed);
                float back  = get_noise_density_at(x, y, z+1, seed);

                bool has_empty_space = false;
                if (up <= _density || down <= _density || left <= _density || right <= _density || front <= _density || back <= _density) has_empty_space = true;

                if (density > _density && has_empty_space) {
                    mi::Vec3 position = mi::Vec3((x - s/2) * CUBE_SIZE, (y - s/2) * CUBE_SIZE, (z - s/2) * CUBE_SIZE);

                    mi_inheritable::Entity* en = new Cube(cbuffer);
                    mesh.add_entity(en, position, mi::Vec3(), mi::Vec3(1.0));
                    en->position = position;
                    en->size = mi::Vec3(CUBE_SIZE);
                    MI_addStaticCamera(scene1, shadowCamera);
                    MI_entityAssignShaderCode(en, shadowShader);
                    MI_sceneAddEntity(scene1, en);
                }
            }
        }
    }
    MI_startMainLoop(scene1.scene_name);
}