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

    #define DEBUG_SEED 14121.40
    #define s 40
    #define FREQ 10.2

    for (int x = 0; x < s; x++) {
        for (int y = 0; y < s; y++) {
            for (int z = 0; z < s; z++) {

                float xNoise, yNoise, zNoise;

                xNoise = mi::noise(y/FREQ, z/FREQ, DEBUG_SEED);
                yNoise = mi::noise(x/FREQ, z/FREQ, DEBUG_SEED);
                zNoise = mi::noise(x/FREQ, y/FREQ, DEBUG_SEED);

                if (xNoise + yNoise + zNoise > 0.8) {
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