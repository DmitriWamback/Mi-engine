// ENGINE
#include "MiCore/engine.h"
#include "scenes/main_scene.h"

/* Main method */

Mi::Inheritable::Scene* scene1 = new MainScene("Hello");

int main() {

    Mi::Engine::MiCoreBegin(1200, 800, "Mi");

    renderbuf cbuffer = renderbuf();
    renderbuf mesh_buf = renderbuf();
    Mi::Mesh mesh = Mi::Mesh(mesh_buf);

    std::string faces[6] = {
        "src/res/images/skyboxF.jpg",
        "src/res/images/skyboxF.jpg",
        "src/res/images/skyboxT.jpg",
        "src/res/images/skyboxB.jpg",
        "src/res/images/skyboxF.jpg",
        "src/res/images/skyboxF.jpg"
    };

    Mi::Inheritable::Renderable* skybox = new Mi::Skybox(mesh_buf, faces);
    skybox->size = glm::vec3(1000.0);
    skybox->position = glm::vec3(0.0);

    /* SHADER DEFINITIONS HERE */
    Shader shadowShader("shadow/vMain.glsl", "shadow/fMain.glsl", "SHADOW SHADER");
    Shader debugShader2("debug/vMain.glsl", "debug/fMain1.glsl", "RED");
    Shader skyboxShader("skybox/vMain.glsl", "skybox/fMain.glsl", "SKYBOX");
    Shader debugModelShader("model/vMain.glsl", "model/fMain.glsl", "MODEL DEBUG");
    Shader instancedShader("instancing/vInstance.glsl", "instancing/fInstance.glsl", "INSTANCED SHADER");
    Shader wireframeShader("wireframe/vMain.glsl", "wireframe/fMain.glsl", "WIREFRAME");
    Shader uiShader("ui/uvMain.glsl", "ui/ufMain.glsl", "UI SHADER");
    Mi::Engine::MiCoreAddShader(shadowShader);
    Mi::Engine::MiCoreAddShader(instancedShader);
    Mi::Engine::MiCoreAddShader(skyboxShader);
    Mi::Engine::MiCoreAddShader(debugModelShader);
    Mi::Engine::MiCoreAddShader(wireframeShader);
    Mi::Engine::MiCoreAddShader(uiShader);

    Mi::StaticCamera shadowCamera = Mi::StaticCamera(Mi::STATICCAMERAPROPERTIES_ORTHOGRAPHIC(), "DEPTH TEXTURE");

    float seed = rand() % 100000;
    //seed = 4730;
    float CUBE_SIZE = 1.0;
    float _density = 0.1;

    LOG_OUT("Running Mi Engine");

    Mi::Engine::MiCoreAddStaticCamera(scene1, shadowCamera);
    Mi::Engine::MiCoreEntityAssignShader(skybox, skyboxShader);
    Mi::Engine::MiCoreSceneAddEntity(scene1, skybox);

    Mi::InstancedRenderer renderer = Mi::InstancedRenderer(new Cube(renderbuf()), false, "test");
    //renderer.AddTransformation(glm::vec3(0.0), glm::vec3(), glm::vec3(1.0));

    float s = rand() % 100000;

    int __size = 1000;

    for (int x = 0; x < __size; x++) {
        for (int z = 0; z < __size; z++) {

            float y = Mi::abs_noise_layer(x/15.f, z/15.f, 2.f, 0.5f, s, 5) * 4;

            renderer.AddTransformation(glm::vec3(x - (float)__size/2.f, floor(y), z - (float)__size/2.f), glm::vec3(), glm::vec3(1.0, 2.0, 1.0));
        }
    }
    //renderer.AddTransformation(glm::vec3(1.0), glm::vec3(), glm::vec3(1.0));
    //renderer.AddTransformation(glm::vec3(2.0), glm::vec3(), glm::vec3(1.0));
    renderer.LinkTransformations();
    renderer.AssignShader(instancedShader);

    Mi::Engine::MiCoreSceneAddInstancedRenderer(scene1, renderer);

    Mi::modelbuf m1, m2;

    Mi::Inheritable::Renderable* m = Mi::IO::LoadModel("src/res/models/monkey2.obj", m2);
    m->size = glm::vec3(5.0);
    m->position = glm::vec3(0.0, 10.0, 0.0);
    Mi::Engine::MiCoreEntityAssignShader(m, shadowShader);
    Mi::Engine::MiCoreSceneAddEntity(scene1, m);

    Mi::UI::UIRenderer urenderer = Mi::UI::UIRenderer("ui1");
    Mi::Inheritable::UIElement* elem = new Mi::UI::UIFrame(renderbuf(), glm::vec2(600.f, 400.f), glm::vec2(200.f));
    Mi::UI::UIElementAssignShader(elem, uiShader);
    urenderer.AddUIElement(elem);

    //Mi::Engine::MiCoreSceneAddUIRenderer(scene1, urenderer);

    Mi::Inheritable::Keyboard* k = new MainKeyboard(scene1);
    Mi::Engine::MiCoreSetSubKeyboard(k);

    glm::vec2 cubeSize = glm::vec2(10, 40);
    int xzSize = 5;
    
    /*
    for (int x = 0; x < xzSize; x++) {
        for (int y = 0; y < xzSize; y++) {
            mi_inheritable::Entity* cubeNoise = new mi::CubeNoise(cbuffer, glm::vec3((x-(xzSize/2))*cubeSize.x, 0, (y-(xzSize/2))*cubeSize.x), cubeSize, seed);
            
            Mi::Engine::MiCoreEntityAssignShader(cubeNoise, shadowShader);
            Mi::Engine::MiCoreEntityAssignWireframeShader(cubeNoise, wireframeShader);
            Mi::Engine::MiCoreSceneAddEntity(scene1, cubeNoise);
        }
    }
    */

    Mi::Engine::MiCoreStartMainLoop(scene1->scene_name);
}