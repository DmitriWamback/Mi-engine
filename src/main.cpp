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

Scene scene1 = Scene("hello");

#define DEBUG_SEED 14121.40
#define s 70

#define FREQ 12.2

float get_noise_density_at(int x, int y, int z, float seed) {
    float xNoise, yNoise, zNoise;
    xNoise = mi::noise(y/FREQ, z/FREQ, seed);
    yNoise = mi::noise(x/FREQ, z/FREQ, seed);
    zNoise = mi::noise(x/FREQ, y/FREQ, seed);

    return xNoise + yNoise + zNoise;
}

int main() {
    __engineBegin();

    renderbuf buffer = renderbuf();
    Entity* e = new Cube(buffer);

    /* SHADER DEFINITIONS HERE */
    Shader shadowShader("shadow/vMain.glsl", "shadow/fMain.glsl", "SHADOW SHADER");
    Shader debugShader2("debug/vMain.glsl", "debug/fMain1.glsl", "RED");
    MI_addShader(shadowShader);
    MI_addShader(debugShader2);

    mi::StaticCamera shadowCamera = mi::StaticCamera(mi::STATICCAMERAPROPERTIES_ORTHOGRAPHIC(), "DEPTH TEXTURE");

    float seed = rand() % 100000;

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
                if (up <= 0.8 || down <= 0.8 || left <= 0.8 || right <= 0.8 || front <= 0.8 || back <= 0.8) has_empty_space = true;

                if (density > 0.8 && has_empty_space) {
                    mi::Vec3 position = mi::Vec3(x - s/2, y - s/2, z - s/2);

                    Entity* en = new Cube(buffer);
                    en->position = position;
                    MI_addStaticCamera(scene1, shadowCamera);
                    MI_entityAssignShaderCode(en, shadowShader);
                    MI_sceneAddEntity(scene1, en);
                }
            }
        }
    }
    MI_startMainLoop(scene1.scene_name);
}