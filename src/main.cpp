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
#include "MiCore/extern.h"
// MATH
#include "math/vector.h"
#include "math/matrix.h"
#include "math/noise.h"
// ENGINE
#include "MiCore/engine.h"
#include "scenes/main_scene.h"

/* Main method */

mi_inheritable::Scene* scene1 = new MainScene("Hello");

#define s 60

#define FREQ 19.2

float get_noise_density_at(int x, int y, int z, float seed) {
    float xNoise, yNoise, zNoise;
    xNoise = mi::noise(y/FREQ, z/FREQ, seed);
    yNoise = mi::noise(x/FREQ, z/FREQ, seed);
    zNoise = mi::noise(x/FREQ, y/FREQ, seed);

    return xNoise + yNoise + zNoise;
}

int main() {

    mi_engine::__engineBegin();

    renderbuf cbuffer = renderbuf();
    renderbuf mesh_buf = renderbuf();
    mi::Mesh mesh = mi::Mesh(mesh_buf);

    std::string faces[6] = {
        "src/res/images/brick.jpg",
        "src/res/images/brick.jpg",
        "src/res/images/brick.jpg",
        "src/res/images/brick.jpg",
        "src/res/images/brick.jpg",
        "src/res/images/brick.jpg"
    };

    mi_inheritable::Entity* skybox = new mi::Skybox(mesh_buf, faces);
    skybox->size = mi::Vec3(100.0);

    /* SHADER DEFINITIONS HERE */
    Shader shadowShader("shadow/vMain.glsl", "shadow/fMain.glsl", "SHADOW SHADER");
    Shader debugShader2("debug/vMain.glsl", "debug/fMain1.glsl", "RED");
    Shader skyboxShader("skybox/vMain.glsl", "skybox/fMain.glsl", "SKYBOX");
    mi_engine::MI_addShader(shadowShader);
    mi_engine::MI_addShader(debugShader2);
    mi_engine::MI_addShader(skyboxShader);

    mi::StaticCamera shadowCamera = mi::StaticCamera(mi::STATICCAMERAPROPERTIES_ORTHOGRAPHIC(), "DEPTH TEXTURE");

    float seed = rand() % 100000;
    //seed = 32193;
    float CUBE_SIZE = 1.0;
    float _density = 0.4;

    std::cout << seed << std::endl;

    mi_engine::MI_addStaticCamera(scene1, shadowCamera);
    mi_engine::MI_entityAssignShaderCode(skybox, debugShader2);
    mi_engine::MI_sceneAddEntity(scene1, skybox);

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
                    en->position = position;
                    en->size = mi::Vec3(CUBE_SIZE);
                    mesh.add_entity(en);
                    mi_engine::MI_entityAssignShaderCode(en, shadowShader);
                    mi_engine::MI_sceneAddEntity(scene1, en);
                }
            }
        }
    }
    mesh.initialize();
    mi_inheritable::Entity* m = &mesh;
    //mi_engine::MI_entityAssignShaderCode(m, shadowShader);
    //mi_engine::MI_sceneAddEntity(scene1, m);

    mi_engine::MI_startMainLoop(scene1->scene_name);
}