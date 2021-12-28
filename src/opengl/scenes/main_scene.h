class MainKeyboard: public mi_inheritable::Keyboard {
public:

    MainKeyboard(mi_inheritable::Scene* scene) {
        this->scene = scene;
    }

    void Listen() {

        renderbuf r;

        if (GetKeyDown(GLFW_KEY_F)) {
            Shader s = mi_engine::MiCoreFindShader("SHADOW SHADER");
            mi_inheritable::Entity* e = new Cube(r);

            glm::vec3 v = scene->camera.GetMouseRayNormalized();

            e->position = scene->camera.position + (2.f * v);
            e->velocity = v;
            mi_engine::MiCoreEntityAssignShader(e, s);
            mi_engine::MiCoreSceneAddEntity(scene, e);
        }
    }
};

class MainScene: public mi_inheritable::Scene {
public:

    mi::Texture tex;
    mi_inheritable::Framebuffer* fb;

    float t;
    glm::vec3 currentPos;
    glm::vec3 lastPos;

    MainScene(std::string n) {

        // Initialize state
        this->scene_name = n;
        nb_entities = 0;
        nb_cameras = 0;
    }

    mi::CubeMap c;

    // TEXTURE, FRAMEBUFFER + OTHER OPENGL DEFINITIONS HERE
    void MiEngineBegun() {
        tex = mi::Texture("src/res/images/diamondplate.jpg");
        fb = new mi::Depthbuffer(1024 * 10, 1024 * 10);
    }

    void SceneMainLoop(glm::vec2 motion, glm::vec2 rotation) {

        MoveCamera(motion, rotation); // IMPORTANT

        MoveEntities();
        
        // MAIN GAME LOOP HERE
        mi::StaticCamera stC = FindStaticCameraByName("DEPTH TEXTURE");
        stC.set_position(stC.get_start_position() + camera.position);
        stC.set_target(stC.get_start_target() + camera.position);

        currentPos = camera.position / 20.0f;
        currentPos = glm::vec3(floor(currentPos.x), 0, floor(currentPos.z));

        mi::RenderTexture depthMap = LoadSceneThroughFramebuffer(stC, fb);
        ResetViewport();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap.tex_id);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex.tex_id);

        Shader wireframe = mi_core::all_shaders["WIREFRAME"];
        wireframe.use();
        wireframe.setMatr4("projection", camera.projection);
        wireframe.setMatr4("view", camera.view);
        glm::vec3 mouseRay = camera.GetMouseRayNormalized();

        Shader instancedShadowShader = mi_core::all_shaders["INSTANCED SHADER"];
        instancedShadowShader.use();
        instancedShadowShader.setVec3("camera_position", camera.position);
        instancedShadowShader.setVec3("mouse_ray", mouseRay);
        instancedShadowShader.setVec3("camera_position", camera.position);
        instancedShadowShader.setMatr4("projection", camera.projection);
        instancedShadowShader.setMatr4("view", camera.view);
        instancedShadowShader.setMatr4("lightSpaceMatrix_projection", camera.lightSpaceMatrix_projection);
        instancedShadowShader.setMatr4("lightSpaceMatrix_view", camera.lightSpaceMatrix_view);
        instancedShadowShader.setVec3("directional_shadow_light_position", stC.get_current_position() - stC.get_current_target());
        instancedShadowShader.setInt("main_tex", 1);
        instancedShadowShader.setInt("depthMap", 0);
        instancedShadowShader.setInt("skybox", 2);
        instancedShadowShader.setFloat("biasOffset", biasOffset);
        instancedShadowShader.setFloat("sCameraFarPlane", stC.zfar);
        

        // rendering entities
        for (int en = 0; en < nb_entities; en++) {
            mi_inheritable::Entity* entity = allEntities[en];
            Shader shader = mi_core::all_shaders[entity->shaderToUse];

            if (entity->type == mi_enum::ENT_SKYBOX) {
                entity->position = camera.position;
            }

            if (shader.shaderName == "SKYBOX") {
                glCullFace(GL_FRONT);
                mi::Skybox* skybox = dynamic_cast<mi::Skybox*>(entity);
                c = skybox->cubemap;
            }

            shader.use();
            shader.setVec3("mouse_ray", mouseRay);
            shader.setVec3("camera_position", camera.position);
            shader.setMatr4("projection", camera.projection);
            shader.setMatr4("view", camera.view);
            shader.setMatr4("lightSpaceMatrix_projection", camera.lightSpaceMatrix_projection);
            shader.setMatr4("lightSpaceMatrix_view", camera.lightSpaceMatrix_view);

            glm::vec3 _cam;
            if (stC.get_current_position() - glm::vec3(camera.position.x, 0, camera.position.z) == stC.get_start_position()) _cam = stC.get_start_position();
            else _cam = stC.get_current_position();

            shader.setVec3("directional_shadow_light_position", stC.get_current_position() - stC.get_current_target());
            shader.setInt("main_tex", 1);
            shader.setInt("depthMap", 0);
            shader.setInt("skybox", 2);
            shader.setFloat("biasOffset", biasOffset);
            shader.setFloat("sCameraFarPlane", stC.zfar);

            if (c.isActive) {
                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_CUBE_MAP, c.tex_id);
            }
            if (entity != nullptr) {
                entity->render(shader);
                //entity->renderWithWireFrame(shader, wireframe);
            }

            if (shader.shaderName == "SKYBOX") glCullFace(GL_BACK);
        }

        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, 0);
        //glActiveTexture(GL_TEXTURE1);
        //glBindTexture(GL_TEXTURE_2D, 0);

        // Rendering UIs
        for (int i = 0; i < uiRenderers.size(); i++) {
            uiRenderers.at(i).Update();
        }

        // using instanced renderers
        mi::InstancedRenderer r = FindRendererByName("test");
        Shader shader = mi_core::all_shaders[r.shaderName];
        shader.use();
        shader.setMatr4("projection", camera.projection);
        shader.setMatr4("view", camera.view);

        r.Render(shader);
    }
};