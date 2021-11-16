#define __SCENE_MAX_ENTITIES 100000

int nb_entities = 0;
namespace mi_core {
    std::map<std::string, Shader> all_shaders;
}

class Scene {
private:

public:
    Entity* allEntities[__SCENE_MAX_ENTITIES];

    mi::Matr4 projection;
    mi::Matr4 view;
    mi::Matr4 model;

    mi::Camera camera;
    std::string scene_name;

    Scene() {}

    Scene(std::string scene_name) {

        this->scene_name = scene_name;

        projection = perspective(90.0, 1.0, 1000.0, 0.1);
        view = lookat(mi::Vec3(5.0, 5.0, 5.0), mi::Vec3(0.0, 0.0, 0.0), mi::Vec3(0.0, 1.0, 0.0));
        model = rotate(mi::Vec3(30.0, 60.0, 90.0));
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

    void add_entity(Entity* entity) {
        allEntities[nb_entities] = entity;
        nb_entities++;
    }

    void render_all(mi::Vec2 motion, mi::Vec2 camera_rotation) {
        renderEntityFromShaderCode(motion, camera_rotation);
    }
};