#include "MiCore/libs.h"
// ENGINE
#include "MiCore/engine.h"
#include "scenes/main_scene.h"

/* Main method */

mi_inheritable::Scene* scene1 = new MainScene("Hello");

int main() {

    mi_engine::MiCoreBegin();

    renderbuf cbuffer = renderbuf();
    renderbuf mesh_buf = renderbuf();
    mi::Mesh mesh = mi::Mesh(mesh_buf);

    std::string faces[6] = {
        "src/res/images/skyboxF.jpg",
        "src/res/images/skyboxF.jpg",
        "src/res/images/skyboxT.jpg",
        "src/res/images/skyboxB.jpg",
        "src/res/images/skyboxF.jpg",
        "src/res/images/skyboxF.jpg"
    };

    mi_inheritable::Entity* skybox = new mi::Skybox(mesh_buf, faces);
    skybox->size = mi::Vec3(1000.0);
    skybox->position = mi::Vec3(0.0);


    struct mi_audio::ADOPROP prop;
    prop.looped = true;
    prop.pitch = 1.0;
    prop.position = mi::Vec3();
    prop.velocity = mi::Vec3();
    prop.volume = 10.0;

    //mi_audio::AudioSource source = mi_audio::AudioSource(prop, "file", "DRM");

    //mi_engine::MiCoreAddAudioSource(source);
    //mi_engine::MiCorePlaySource(source.name);

    /* SHADER DEFINITIONS HERE */
    Shader shadowShader("shadow/vMain.glsl", "shadow/fMain.glsl", "SHADOW SHADER");
    Shader debugShader2("debug/vMain.glsl", "debug/fMain1.glsl", "RED");
    Shader skyboxShader("skybox/vMain.glsl", "skybox/fMain.glsl", "SKYBOX");
    mi_engine::MiCoreAddShader(shadowShader);
    mi_engine::MiCoreAddShader(debugShader2);
    mi_engine::MiCoreAddShader(skyboxShader);

    mi::StaticCamera shadowCamera = mi::StaticCamera(mi::STATICCAMERAPROPERTIES_ORTHOGRAPHIC(), "DEPTH TEXTURE");

    float seed = rand() % 100000;
    float CUBE_SIZE = 1.0;
    float _density = 0.1;

    //const float* v = load_model_vertices("src/res/models/tree.obj");
    std::cout << seed << std::endl;

    mi_engine::MiCoreAddStaticCamera(scene1, shadowCamera);
    mi_engine::MiCoreEntityAssignShaderCode(skybox, skyboxShader);
    mi_engine::MiCoreSceneAddEntity(scene1, skybox);

    int cubeSize = 25;
    int xzSize = 5;

    for (int x = 0; x < xzSize; x++) {
        for (int y = 0; y < xzSize; y++) {
            mi_inheritable::Entity* cubeNoise = new mi::CubeNoise(cbuffer, mi::Vec3((x-(xzSize/2))*cubeSize, 0, (y-(xzSize/2))*cubeSize), cubeSize, seed);
            
            mi_engine::MiCoreEntityAssignShaderCode(cubeNoise, shadowShader);
            mi_engine::MiCoreSceneAddEntity(scene1, cubeNoise);
        }
    }

    mi_engine::MiCoreStartMainLoop(scene1->scene_name);
}