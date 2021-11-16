#define __SCENE_MAX_ENTITIES 100000

int nb_entities = 0;
namespace mi_core {
    std::map<std::string, Shader> all_shaders;
}

class Scene {
private:

    Entity* allEntities[__SCENE_MAX_ENTITIES];

    mi::Matr4 projection;
    mi::Matr4 view;

    mi::Camera camera;

public:
    std::string scene_name;

    Scene() {}

    Scene(std::string scene_name) {

        this->scene_name = scene_name;

        projection = perspective(90.0, 1.0, 1000.0, 0.1);
        view = lookat(mi::Vec3(5.0, 5.0, 5.0), mi::Vec3(0.0, 0.0, 0.0), mi::Vec3(0.0, 1.0, 0.0));
    }
    
    void renderEntityFromShaderCode(mi::Vec2 motion, mi::Vec2 camera_rotation) {

        camera.rotateCamera(camera_rotation.x, camera_rotation.y);
        camera.moveCamera(1.0, motion);

        for (int en = 0; en < nb_entities; en++) {
            Entity* entity = allEntities[en];

            //Shader shader = shaders.find(entity->shaderCode);
            //std::cout << shader.shaderName << " " << entity->shaderCode << " " << shaders.size() << std::endl;
            Shader shader = mi_core::all_shaders[entity->shaderToUse];

            shader.use();
            shader.setMatr4("projection", camera.projection);
            shader.setMatr4("view", camera.view);
            //shader.setMatr4("model", model);

            entity->render(shader);
        }
    }

    mi::Vec3 get_camera_position() {
        return camera.position;
    }

    mi::Vec3 get_camera_look_direction() {
        return camera.look_direction;
    }

    mi::Matr4 get_projection() {
        return camera.projection;
    }

    mi::Matr4 get_view() {
        return camera.view;
    }

    void add_entity(Entity* entity) {
        allEntities[nb_entities] = entity;
        nb_entities++;
    }

    void render_all(mi::Vec2 motion, mi::Vec2 camera_rotation) {
        renderEntityFromShaderCode(motion, camera_rotation);
    }
};