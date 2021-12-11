class MainScene: public mi_inheritable::Scene {
private:

    std::vector<mi::InstancedRenderer> instancedRenderer;

public:

    mi::Texture tex;
    mi_inheritable::Framebuffer* fb;

    float t;
    mi::Vec3 currentPos;
    mi::Vec3 lastPos;

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
        fb = new mi::Depthbuffer(1024*10, 1024*10);
    }

    void SceneMainLoop(mi::Vec2 motion, mi::Vec2 rotation) {

        MoveCamera(motion, rotation); // IMPORTANT

        // MAIN GAME LOOP HERE
        mi::StaticCamera stC = FindStaticCameraByName("DEPTH TEXTURE");
        stC.set_position(stC.get_start_position() + mi::Vec3(camera.position.x, 0, camera.position.z));
        stC.set_target(stC.get_start_target() + mi::Vec3(camera.position.x, 0, camera.position.z));

        currentPos = camera.position / 20.0;
        currentPos = mi::Vec3(floor(currentPos.x), 0, floor(currentPos.z));
        //std::cout << currentPos.x << " " << currentPos.y << " " << currentPos.z << std::endl;

        if (currentPos.x != lastPos.x || currentPos.z != lastPos.z) {
            
        }
        t+=0.01;

        lastPos = currentPos;

        mi::RenderTexture depthMap = LoadSceneThroughFramebuffer(stC, fb);
        ResetViewport();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap.tex_id);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex.tex_id);

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

            if (entity->type == mi_enum::ENT_NOISE_CUBE) {
                mi::CubeNoise* nc = dynamic_cast<mi::CubeNoise*>(entity);
                //c->push_to(mi::Vec3(), 100.0);

                mi::Vec3 p = camera.position - nc->position;
                float m = sqrt(p.x * p.x + p.z * p.z);
                if (m > 100) nc->shouldRender = false;
                else nc->shouldRender = true;
            }

            shader.use();
            shader.setVec3("camera_position", camera.position);
            shader.setMatr4("projection", camera.projection);
            shader.setMatr4("view", camera.view);
            shader.setMatr4("lightSpaceMatrix_projection", camera.lightSpaceMatrix_projection);
            shader.setMatr4("lightSpaceMatrix_view", camera.lightSpaceMatrix_view);

            mi::Vec3 _cam;
            if (stC.get_current_position() - mi::Vec3(camera.position.x, 0, camera.position.z) == stC.get_start_position()) _cam = stC.get_start_position();
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
            }

            if (shader.shaderName == "SKYBOX") glCullFace(GL_BACK);
        }
    }
};