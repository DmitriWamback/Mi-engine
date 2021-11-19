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
    Shader debugShader("debug/vMain.glsl", "debug/fMain1.glsl", "RED");
    Shader debugShader2("debug/vMain.glsl", "debug/fMain2.glsl", "YELLOW");
    MI_addShader(debugShader);
    MI_addShader(debugShader2);

    mi::StaticCamera shadowCamera = mi::StaticCamera(mi::STATICCAMERAPROPERTIES_ORTHOGRAPHIC(), "DEPTH TEXTURE");

    #define DEBUG_SEED 1421.40
    #define s 30

    for (int x = 0; x < s; x++) {
        for (int y = 0; y < s; y++) {
            for (int z = 0; z < s; z++) {

                float xNoise, yNoise, zNoise;

                xNoise = mi::noise(y/6.2, z/6.2, DEBUG_SEED);
                yNoise = mi::noise(x/6.2, z/6.2, DEBUG_SEED);
                zNoise = mi::noise(x/6.2, y/6.2, DEBUG_SEED);

                if (xNoise + yNoise + zNoise > 0.5) {
                    mi::Vec3 position = mi::Vec3(x - s/2, y - s/2, z - s/2);

                    Entity* en = new Cube(buffer);
                    en->position = position;
                    MI_addStaticCamera(scene1, shadowCamera);
                    MI_entityAssignShaderCode(en, debugShader);
                    MI_sceneAddEntity(scene1, en);
                }
            }
        }
    }
    MI_startMainLoop(scene1.scene_name);
}