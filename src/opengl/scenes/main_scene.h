class MainKeyboard: public Mi::Inheritable::Keyboard {
public:

    MainKeyboard(Mi::Inheritable::Scene* scene) {
        this->scene = scene;
    }

    void Listen() {
    }
};

class MainScene: public Mi::Inheritable::Scene {
private:
    Mi::Inheritable::Framebuffer* fb;
    Mi::Texture tex;
    Mi::DeferredRenderer* dr;

public:

    MainScene(std::string n) {
        this->scene_name = n;
    }

    // TEXTURE, FRAMEBUFFER + OTHER OPENGL DEFINITIONS HERE
    void MiEngineBegun() {
        fb = new Mi::Depthbuffer(3000, 3000);
        tex = Mi::Texture::Create("src/res/images/diamondplate.jpg");
        Mi::StaticCamera cam = Mi::StaticCamera(Mi::STATICCAMERAPROPERTIES_ORTHOGRAPHIC(), "Depth");
        AddStaticCamera(cam);

        dr = Mi::DeferredRenderer::Create();

        Mi::Renderable t = Mi::Renderable::Create();
        t.AttachRenderer(new Mi::CubeRenderer(RenderBuffer::Create()));

        Mi::Renderable* terrain = FindRenderable("Terrain");
        terrain->SetTexture(0, "src/res/images/Unknown.jpeg");
        terrain->SetTexture(1, "src/res/images/normal.jpg");
        terrain->SetTexture(2, "src/res/images/heightmap.jpeg");
        terrain->rotation = glm::vec3(0.0, 0.0, 0.0);
        terrain->position = glm::vec3(0.0, 0.0, 0.0);
        terrain->size = glm::vec3(1.0f);
        terrain->opacity = 1.f;

        dr->AddRenderable(t);

        Mi::TextRenderer* textRenderer = FindRenderable("TEXT")->TryGetRenderer<Mi::TextRenderer*>();
        textRenderer->font = Mi::IO::Font::Create("src/Cinzel-Regular.ttf");
        textRenderer->text = "Hello";
    }

    void SceneMainLoop(glm::vec2 motion, glm::vec2 rotation) {
        MoveCamera(motion, rotation); // IMPORTANT
        MoveEntities();
        
        // MAIN GAME LOOP HERE

        glm::vec3 currentPos;

        currentPos = camera.position / 20.0f;
        currentPos = glm::vec3(floor(currentPos.x), 0, floor(currentPos.z));

        dr->Render(camera);
        std::map<const char*, uint32_t> textures = dr->GetBuffers(camera);
        ResetViewport();

        Mi::InstancedRenderer r = FindRendererByName("INSTANCED TEST");
        Mi::Shader rs = Mi::Engine::MiCoreFindShader(r.shaderName);
        
        rs.use();
        rs.setMatr4("projection", camera.projection);
        rs.setMatr4("view", camera.view);
        r.Render(rs);

        if (GetKeyDown(GLFW_KEY_E)) {
            Mi::Renderable* r = FindRenderable("Terrain");
            r->rotation.y += 0.2;
        }
        if (GetKeyDown(GLFW_KEY_Q)) {
            Mi::Renderable* r = FindRenderable("Terrain");
            r->rotation.y -= 0.2;
        }

        glm::vec3 mouseRay = camera.GetMouseRayNormalized();
        // rendering entities

        std::vector<Mi::Renderable> transparent = Mi::RenderFurtherest(Mi::GetTransparents(renderableCollection), camera.position);
        std::vector<Mi::Renderable> solids      = Mi::GetSolids(renderableCollection);

        for (int en = 0; en < solids.size(); en++) {
            Mi::Renderable entity = solids[en];
            Mi::Shader s = Mi::Engine::MiCoreFindShader(entity.shaderName);
            s.use();
            s.setVec3("camera_position", camera.position);
            Render(entity);
        }

        for (int en = 0; en < transparent.size(); en++) {
            Mi::Renderable entity = transparent[en];
            Render(entity);
        }

        // Setting Text
        Mi::TextRenderer* textRenderer = FindRenderable("TEXT")->TryGetRenderer<Mi::TextRenderer*>();
        textRenderer->text = "Time: " + std::to_string(glfwGetTime()/3.f);
        textRenderer->color = glm::vec3(1.f, 1.f, 0.f);
    }

    void Render(Mi::Renderable entity) {
        

        Mi::StaticCamera stC = FindStaticCameraByName("Depth");

        glm::mat4 a = glm::lookAt(glm::vec3(200.f, 100.f, 100.f) + camera.position, glm::vec3(0.f) + camera.position, glm::vec3(0.0f, 1.f, 0.f));
        stC.view = a;

        stC.set_position(stC.GetStartPosition() + camera.position);
        stC.set_target(stC.GetStartPosition() + camera.position);

        Mi::RenderTexture depthMap = LoadSceneThroughFramebuffer(stC.projection, a, fb, false);
        ResetViewport();

        glm::vec3 mouseRay = camera.GetMouseRayNormalized();

        Mi::Shader shader = Mi::Engine::MiCoreFindShader(entity.shaderName);
        
        glCullFace(GL_BACK);
        shader.use();
        shader.setVec3("mouse_ray", mouseRay);
        shader.setVec3("camera_position", camera.position);

        shader.setMatr4("projection", camera.projection);
        shader.setMatr4("view", camera.view);
        shader.setMatr4("lightSpaceMatrix_projection", stC.projection);
        shader.setMatr4("lightSpaceMatrix_view", a);
        shader.setVec3("directional_shadow_light_position", stC.GetCurrentPosition() - stC.GetCurrentTarget());
        //shader.setInt("main_tex", 1);
        //shader.setInt("depthMap", 0);
        depthMap.Bind(3);
        shader.setInt("skybox", 2);
        shader.setFloat("biasOffset", biasOffset);
        shader.setFloat("sCameraFarPlane", stC.zfar);

        entity.render(shader);
        glEnable(GL_CULL_FACE);
    }
};