class MainScene: public mi_inheritable::Scene {
public:

    mi::Texture tex;
    mi_inheritable::Framebuffer* fb;

    float t;

    MainScene(std::string n) {

        // Initialize state
        this->scene_name = n;
        nb_entities = 0;
        nb_cameras = 0;
    }

    // TEXTURE, FRAMEBUFFER + OTHER OPENGL DEFINITIONS HERE
    void MiEngineBegun() {
        tex = mi::Texture("src/res/images/brick.jpg");
        fb = new mi::Depthbuffer(1024*5, 1024*5);
    }

    void SceneMainLoop(mi::Vec2 motion, mi::Vec2 rotation) {

        MoveCamera(motion, rotation); // IMPORTANT

        // MAIN GAME LOOP HERE
        mi::StaticCamera stC = FindStaticCameraByName("DEPTH TEXTURE");
        mi::RenderTexture depthMap = LoadSceneThroughFB(stC, fb);
        ResetViewport();

        //static_cameras[0].set_position(mi::Vec3(sin(t)*300, 50.0, cos(t)*300));
        //t += 0.1;

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap.tex_id);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex.tex_id);

        for (int en = 0; en < nb_entities; en++) {
            mi_inheritable::Entity* entity = allEntities[en];
            Shader shader = mi_core::all_shaders[entity->shaderToUse];

            shader.use();
            shader.setVec3("camera_position", camera.position);
            shader.setMatr4("projection", camera.projection);
            shader.setMatr4("view", camera.view);
            shader.setMatr4("lightSpaceMatrix_projection", camera.lightSpaceMatrix_projection);
            shader.setMatr4("lightSpaceMatrix_view", camera.lightSpaceMatrix_view);
            shader.setVec3("directional_shadow_light_position", camera_pos);
            shader.setInt("main_tex", 1);
            shader.setInt("depthMap", 0);
            shader.setFloat("biasOffset", biasOffset);
            shader.setFloat("sCameraFarPlane", stC.zfar);

            entity->render(shader);
        }
    }
};