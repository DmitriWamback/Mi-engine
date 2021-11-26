class MainScene: public mi_inheritable::Scene {
public:

    MainScene(std::string n) {
        this->scene_name = n;
        nb_entities = 0;
        nb_cameras = 0;
    }

    void SceneMainLoop(mi::Vec2 motion, mi::Vec2 rotation) {

        move_camera(motion, rotation);

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
};