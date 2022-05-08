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

    Mi::Engine::MiCoreAddShader(shadowShader);
    Mi::Engine::MiCoreAddShader(instancedShader);

    Mi::System* _s = Mi::ParticleSystem::Create();
    RenderBuffer renderbuf = RenderBuffer::Create();
    Mi::InstancedRenderer r = Mi::InstancedRenderer::Create(new Mi::QuadRenderer(renderbuf),
                                                            false,
                                                            "INSTANCED TEST");

    Mi::Inheritable::Keyboard* k = new MainKeyboard(scene1);
    Mi::Engine::MiCoreSetSubKeyboard(k);

    Mi::Renderable a = Mi::Renderable::Create();
    a.AttachRenderer(new Mi::TerrainRenderer(RenderBuffer::Create()));
    a.size = glm::vec3(10.5f);
    a.name = "Terrain";
    Mi::TerrainRenderer* renderer = a.TryGetRenderer<Mi::TerrainRenderer*>();

    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            
            float height = Mi::noise(x / 13.f, y / 13.f, 145.3f) + 1.f;
            float px = x + std::rand()%2 - 1.f - 50;
            float pz = y + std::rand()%2 - 1.f - 50;

            float p = renderer->GetHeightAt(glm::vec2(px, pz));

            if (Mi::noise(x / 13.f, y / 13.f, 145.3f) > -0.5f) {
                r.AddTransformation(glm::vec3(px, p + height/2, pz), 
                                    glm::vec3(0.f, std::rand()%10000, 0.f), 
                                    glm::vec3(1.0f, height, 1.0f));
            }
        }
    }
    r.AssignShader(instancedShader);
    r.LinkTransformations();
    Mi::Engine::MiCoreSceneAddInstancedRenderer(scene1, r);


    Mi::Renderable b = Mi::Renderable::Create();
    b.AttachRenderer(new Mi::CubeRenderer(renderbuf));
    scene1->AddEntity(b);

    RenderBuffer rb = RenderBuffer::Create();

    a.shaderName = standard.shaderName;
    scene1->AddEntity(a);

    Mi::Engine::MiCoreAddScene(scene1);
    Mi::Engine::MiCoreStartMainLoop(scene1->scene_name);
}