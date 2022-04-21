// ENGINE
#include "mi-core/engine.h"
#include "scenes/main_scene.h"

/* Main method */

Mi::Inheritable::Scene* scene1 = new MainScene("Hello");

int main() {

    Mi::Engine::MiCoreBegin(1200, 800, "Mi");

    std::string faces[6] = {
        "src/res/images/skyboxF.jpg",
        "src/res/images/skyboxF.jpg",
        "src/res/images/skyboxT.jpg",
        "src/res/images/skyboxB.jpg",
        "src/res/images/skyboxF.jpg",
        "src/res/images/skyboxF.jpg"
    };

    Mi::Shader shadowShader     = Mi::Shader::Create("shadow/vMain.glsl", "shadow/fMain.glsl", "SHADOW SHADER");
    Mi::Shader debugShader2     = Mi::Shader::Create("debug/vMain.glsl", "debug/fMain1.glsl", "RED");
    Mi::Shader skyboxShader     = Mi::Shader::Create("skybox/vMain.glsl", "skybox/fMain.glsl", "SKYBOX");
    Mi::Shader debugModelShader = Mi::Shader::Create("model/vMain.glsl", "model/fMain.glsl", "MODEL DEBUG");
    Mi::Shader instancedShader  = Mi::Shader::Create("instancing/vInstance.glsl", "instancing/fInstance.glsl", "INSTANCED SHADER");
    Mi::Shader wireframeShader  = Mi::Shader::Create("wireframe/vMain.glsl", "wireframe/fMain.glsl", "WIREFRAME");
    Mi::Shader uiShader         = Mi::Shader::Create("ui/uvMain.glsl", "ui/ufMain.glsl", "UI SHADER");
    Mi::Shader standard         = Mi::Shader::Create("standard/vMain.glsl", "standard/fMain.glsl", "standard");

    Mi::Engine::MiCoreAddShader(standard);

    Mi::System* _s = Mi::ParticleSystem::Create();

    Mi::Inheritable::Keyboard* k = new MainKeyboard(scene1);
    Mi::Engine::MiCoreSetSubKeyboard(k);

    glm::vec2 cubeSize = glm::vec2(10, 40);
    int xzSize = 5;
    
    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            Mi::Renderable r = Mi::Renderable::Create();
            r.position = glm::vec3(x, sin(x), y);
            r.AttachAttribute(new Mi::CubeRenderer(RenderBuffer::Create()));
            r.shaderToUse = standard.shaderName;
            scene1->AddEntity(r);
        }
    }

    Mi::Engine::MiCoreAddScene(scene1);
    Mi::Engine::MiCoreStartMainLoop(scene1->scene_name);
}