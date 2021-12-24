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
    skybox->size = glm::vec3(1000.0);
    skybox->position = glm::vec3(0.0);


    struct mi_audio::ADOPROP prop;
    prop.looped = true;
    prop.pitch = 1.0;
    prop.position = glm::vec3();
    prop.velocity = glm::vec3();
    prop.volume = 10.0;

    //mi_audio::AudioSource source = mi_audio::AudioSource(prop, "file", "DRM");

    //mi_engine::MiCoreAddAudioSource(source);
    //mi_engine::MiCorePlaySource(source.name);

    /* SHADER DEFINITIONS HERE */
    Shader shadowShader("shadow/vMain.glsl", "shadow/fMain.glsl", "SHADOW SHADER");
    Shader debugShader2("debug/vMain.glsl", "debug/fMain1.glsl", "RED");
    Shader skyboxShader("skybox/vMain.glsl", "skybox/fMain.glsl", "SKYBOX");
    Shader debugModelShader("model/vMain.glsl", "model/fMain.glsl", "MODEL DEBUG");
    Shader instancedShader("instancing/vInstance.glsl", "instancing/fInstance.glsl", "INSTANCED SHADER");
    Shader wireframeShader("wireframe/vMain.glsl", "wireframe/fMain.glsl", "WIREFRAME");
    Shader uiShader("ui/uvMain.glsl", "ui/ufMain.glsl", "UI SHADER");
    mi_engine::MiCoreAddShader(shadowShader);
    mi_engine::MiCoreAddShader(instancedShader);
    mi_engine::MiCoreAddShader(skyboxShader);
    mi_engine::MiCoreAddShader(debugModelShader);
    mi_engine::MiCoreAddShader(wireframeShader);
    mi_engine::MiCoreAddShader(uiShader);

    mi::StaticCamera shadowCamera = mi::StaticCamera(mi::STATICCAMERAPROPERTIES_ORTHOGRAPHIC(), "DEPTH TEXTURE");

    float seed = rand() % 100000;
    //seed = 4730;
    float CUBE_SIZE = 1.0;
    float _density = 0.1;

    LOG_OUT("Running Mi Engine");

    mi_engine::MiCoreAddStaticCamera(scene1, shadowCamera);
    mi_engine::MiCoreEntityAssignShader(skybox, skyboxShader);
    mi_engine::MiCoreSceneAddEntity(scene1, skybox);

    mi::InstancedRenderer renderer = mi::InstancedRenderer(new Cube(renderbuf()), "test");
    //renderer.AddTransformation(glm::vec3(0.0), glm::vec3(), glm::vec3(1.0));

    float s = rand() % 100000;

    for (int x = 0; x < 1000; x++) {
        for (int z = 0; z < 1000; z++) {

            float y = mi::noise_layer(x/15.f, z/15.f, 6.f, 0.5f, s, 20) * 5.f;

            renderer.AddTransformation(glm::vec3(x - 500.f, floor(y), z - 500.f), glm::vec3(), glm::vec3(1.0));
        }
    }
    //renderer.AddTransformation(glm::vec3(1.0), glm::vec3(), glm::vec3(1.0));
    //renderer.AddTransformation(glm::vec3(2.0), glm::vec3(), glm::vec3(1.0));
    renderer.LinkTransformations();
    renderer.AssignShader(instancedShader);

    mi_engine::MiCoreSceneAddInstancedRenderer(scene1, renderer);

    mi::modelbuf m1, m2;

    mi_inheritable::Entity* m = mi::LoadModel("src/res/models/monkey2.obj", m2);
    m->size = glm::vec3(2.0);
    m->position = glm::vec3(0.0);
    mi_engine::MiCoreEntityAssignShader(m, shadowShader);
    mi_engine::MiCoreSceneAddEntity(scene1, m);

    mi_ui::UIRenderer urenderer = mi_ui::UIRenderer("ui1");
    mi_inheritable::UIElement* elem = new mi_ui::UIFrame(renderbuf(), glm::vec2(600.f, 400.f), glm::vec2(200.f));
    //mi_ui::UIElementAssignShader(elem, uiShader);
    //urenderer.AddUIElement(elem);

    mi_engine::MiCoreSceneAddUIRenderer(scene1, urenderer);

    mi_inheritable::Keyboard* k = new MainKeyboard(scene1);
    mi_engine::MiCoreSetSubKeyboard(k);

    glm::vec2 cubeSize = glm::vec2(10, 40);
    int xzSize = 5;
    
    /*
    for (int x = 0; x < xzSize; x++) {
        for (int y = 0; y < xzSize; y++) {
            mi_inheritable::Entity* cubeNoise = new mi::CubeNoise(cbuffer, glm::vec3((x-(xzSize/2))*cubeSize.x, 0, (y-(xzSize/2))*cubeSize.x), cubeSize, seed);
            
            mi_engine::MiCoreEntityAssignShader(cubeNoise, shadowShader);
            mi_engine::MiCoreEntityAssignWireframeShader(cubeNoise, wireframeShader);
            mi_engine::MiCoreSceneAddEntity(scene1, cubeNoise);
        }
    }
    */

    mi_engine::MiCoreStartMainLoop(scene1->scene_name);
}