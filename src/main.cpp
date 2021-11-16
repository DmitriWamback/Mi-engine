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

    for (int x = 0; x < 100; x++) {
        for (int z = 0; z < 100; z++) {
            mi::Vec3 position = mi::Vec3(x - 50.0, floor(sin(x/2.0) + cos(z/2.0)), z - 50.0);

            Entity* en = new Cube(buffer);
            en->position = position;
            en->rotation = mi::Vec3(0.0);
            MI_entityAssignShaderCode(en, debugShader);
            MI_sceneAddEntity(scene1, en);
        }
    }
    MI_startMainLoop(scene1.scene_name);
}