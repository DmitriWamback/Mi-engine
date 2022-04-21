class MainKeyboard: public Mi::Inheritable::Keyboard {
public:

    MainKeyboard(Mi::Inheritable::Scene* scene) {
        this->scene = scene;
    }

    void Listen() {
    }
};

class MainScene: public Mi::Inheritable::Scene {
public:

    MainScene(std::string n) {
        this->scene_name = n;
    }

    // TEXTURE, FRAMEBUFFER + OTHER OPENGL DEFINITIONS HERE
    void MiEngineBegun() {

    }

    void SceneMainLoop(glm::vec2 motion, glm::vec2 rotation) {
        MoveCamera(motion, rotation); // IMPORTANT
        MoveEntities();
        LOG_OUT(camera.position.x);
        
        // MAIN GAME LOOP HERE
        //Mi::StaticCamera stC = FindStaticCameraByName("DEPTH TEXTURE");
        //stC.set_position(stC.get_start_position() + camera.position);
        //stC.set_target(stC.get_start_target() + camera.position);

        //currentPos = camera.position / 20.0f;
        //currentPos = glm::vec3(floor(currentPos.x), 0, floor(currentPos.z));

        //Mi::RenderTexture depthMap = LoadSceneThroughFramebuffer(stC, fb, false);
        //dr->Render(camera);

        //depthMap.Bind(0);
        // debugging
        //glActiveTexture(GL_TEXTURE1);
        //glBindTexture(GL_TEXTURE_2D, dr->GetBuffers(camera)[MI_DEFERRED_RENDER_NORMAL_KEY]);
        //tex.Bind(1);

        ResetViewport();

        glm::vec3 mouseRay = camera.GetMouseRayNormalized();

        Mi::Shader instancedShadowShader = Mi::Engine::MiCoreFindShader("INSTANCED SHADER");
        instancedShadowShader.use();
        instancedShadowShader.setVec3("camera_position", camera.position);
        instancedShadowShader.setVec3("mouse_ray", mouseRay);
        instancedShadowShader.setVec3("camera_position", camera.position);
        instancedShadowShader.setMatr4("projection", camera.projection);
        instancedShadowShader.setMatr4("view", camera.view);
        instancedShadowShader.setMatr4("lightSpaceMatrix_projection", camera.lightSpaceMatrix_projection);
        instancedShadowShader.setMatr4("lightSpaceMatrix_view", camera.lightSpaceMatrix_view);
        //instancedShadowShader.setVec3("directional_shadow_light_position", stC.get_current_position() - stC.get_current_target());
        instancedShadowShader.setInt("main_tex", 1);
        instancedShadowShader.setInt("depthMap", 0);
        instancedShadowShader.setInt("skybox", 2);
        instancedShadowShader.setFloat("biasOffset", biasOffset);
        //instancedShadowShader.setFloat("sCameraFarPlane", stC.zfar);
        

        // rendering entities
        for (int en = 0; en < renderableCollection.size(); en++) {
            Mi::Renderable entity = renderableCollection[en];
            Mi::Shader shader = Mi::Engine::MiCoreFindShader(entity.shaderToUse);

            if (entity.type == Mi::Enum::ENT_SKYBOX) {
                entity.position = camera.position;
            }

            if (shader.shaderName == "SKYBOX") {
                glCullFace(GL_FRONT);
                //c = skybox->cubemap;
            }

            shader.use();

            shader.setVec3("mouse_ray", mouseRay);
            shader.setVec3("camera_position", camera.position);
            shader.setMatr4("projection", camera.projection);
            shader.setMatr4("view", camera.view);
            shader.setMatr4("lightSpaceMatrix_projection", camera.lightSpaceMatrix_projection);
            shader.setMatr4("lightSpaceMatrix_view", camera.lightSpaceMatrix_view);

            glm::vec3 _cam;
            //if (stC.get_current_position() - glm::vec3(camera.position.x, 0, camera.position.z) == stC.get_start_position()) _cam = stC.get_start_position();
            //else _cam = stC.get_current_position();

            //shader.setVec3("directional_shadow_light_position", stC.get_current_position() - stC.get_current_target());
            shader.setInt("main_tex", 1);
            shader.setInt("depthMap", 0);
            shader.setInt("skybox", 2);
            shader.setFloat("biasOffset", biasOffset);
            //shader.setFloat("sCameraFarPlane", stC.zfar);

            //if (c.isActive) {
            //    glActiveTexture(GL_TEXTURE2);
            //    glBindTexture(GL_TEXTURE_CUBE_MAP, c.tex_id);
            //}
            entity.render(shader);

            if (shader.shaderName == "SKYBOX") glCullFace(GL_BACK);
        }
    }
};