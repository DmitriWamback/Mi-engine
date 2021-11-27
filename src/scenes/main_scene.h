class MainScene: public mi_inheritable::Scene {
public:

    mi::Texture tex;
    mi_inheritable::Framebuffer* fb;

    MainScene(std::string n) {

        // Initialize state
        this->scene_name = n;
        nb_entities = 0;
        nb_cameras = 0;
    }

    void SceneMainLoop(mi::Vec2 motion, mi::Vec2 rotation) {

        move_camera(motion, rotation); // IMPORTANT

        // MAIN GAME LOOP HERE
        mi::RenderTexture depthMap = load_rendered_scene(static_cameras[0], fb);
        reset_viewport();

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

            entity->render(shader);
        }
    }

    // TEXTURE, FRAMEBUFFER + OTHER OPENGL DEFINITIONS HERE
    void mi_engine_begun() {
        tex = mi::Texture("src/res/images/metallic.png");
        fb = new mi::Depthbuffer(10000, 10000);
    }
};