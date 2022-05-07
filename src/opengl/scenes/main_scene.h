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
        fb = new Mi::Depthbuffer(1000, 1000);
        tex = Mi::Texture::Create("src/res/images/diamondplate.jpg");
        Mi::StaticCamera cam = Mi::StaticCamera(Mi::STATICCAMERAPROPERTIES_ORTHOGRAPHIC(), "Depth");
        AddStaticCamera(cam);

        dr = Mi::DeferredRenderer::Create();

        Mi::Renderable t = Mi::Renderable::Create();
        t.AttachRenderer(new Mi::CubeRenderer(RenderBuffer::Create()));

        Mi::Renderable* terrain = FindRenderable("Terrain");
        terrain->SetTexture(0, "src/res/images/brick.jpg");
        terrain->SetTexture(1, "src/res/images/normal.jpg");
        terrain->rotation = glm::vec3(45.0, 0.0, 45.0);
        terrain->position = glm::vec3(0.0, 0.0, 20.0);
        terrain->opacity = 1.f;

        dr->AddRenderable(t);
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
        //depthMap.Bind(0);
        //tex.Bind(1);
        //Mi::Texture::AttemptBind(textures["_normal"], 1);

        Mi::InstancedRenderer r = FindRendererByName("INSTANCED TEST");
        Mi::Shader rs = Mi::Engine::MiCoreFindShader(r.shaderName);

        rs.use();
        rs.setMatr4("projection", camera.projection);
        rs.setMatr4("view", camera.view);
        //r.Render(rs);

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
    }

    void Render(Mi::Renderable entity) {
        

        Mi::StaticCamera stC = FindStaticCameraByName("Depth");
        stC.set_position(stC.GetStartPosition() + camera.position);
        stC.set_target(stC.GetStartPosition() + camera.position);

        Mi::RenderTexture depthMap = LoadSceneThroughFramebuffer(stC, fb, false);
        ResetViewport();

        glm::vec3 mouseRay = camera.GetMouseRayNormalized();

        Mi::Shader shader = Mi::Engine::MiCoreFindShader(entity.shaderName);
        shader.use();

        shader.setVec3("mouse_ray", mouseRay);
        shader.setVec3("camera_position", camera.position);
        shader.setMatr4("projection", camera.projection);
        shader.setMatr4("view", camera.view);
        shader.setMatr4("lightSpaceMatrix_projection", stC.projection);
        shader.setMatr4("lightSpaceMatrix_view", stC.view);

        glm::vec3 _cam;
        if (stC.GetCurrentPosition() - glm::vec3(camera.position.x, 0, camera.position.z) == stC.GetStartPosition()) _cam = stC.GetStartTarget();
        else _cam = stC.GetCurrentPosition();
        stC.set_position(stC.GetStartPosition() + camera.position);
        stC.set_target(stC.GetStartTarget() + camera.position);

        shader.setVec3("directional_shadow_light_position", stC.GetCurrentPosition() - stC.GetCurrentTarget());
        //shader.setInt("main_tex", 1);
        //shader.setInt("depthMap", 0);
        shader.setInt("skybox", 2);
        shader.setFloat("biasOffset", biasOffset);
        shader.setFloat("sCameraFarPlane", stC.zfar);

        entity.render(shader);
    }
};