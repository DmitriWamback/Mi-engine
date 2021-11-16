#define __SCENE_MAX_ENTITIES 100000
#define __SCENE_MAX_STATIC_CAMERAS 10

/* 
-- SCENE --
The scene is a way to easily organize and render several places
*/


namespace mi_core {
    std::map<std::string, Shader> all_shaders;
}

class Scene {
private:

    int nb_entities = 0;
    int nb_cameras = 0;

    Entity* allEntities[__SCENE_MAX_ENTITIES];
    mi::StaticCamera static_cameras[__SCENE_MAX_STATIC_CAMERAS];

    mi::Matr4 projection;
    mi::Matr4 view;

    mi::Camera camera;
    Shader depthShader;

    mi::RenderTexture renderSceneThroughFrameBuffer(mi::StaticCamera c, mi::Framebuffer* framebuffer) {

        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->fbo);
        
        if (framebuffer->type == mi::DEPTH) {

        }
    }

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

            Shader shader = mi_core::all_shaders[entity->shaderToUse];

            shader.use();
            shader.setVec3("camera_position", camera.position);
            shader.setMatr4("projection", camera.projection);
            shader.setMatr4("view", camera.view);

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

    mi::RenderTexture load_rendered_scene(std::string camera_to_render, mi::Framebuffer* framebuffer) {

        mi::StaticCamera camera;

        for (int c = 0; c < nb_cameras; c++) {
            
            if (static_cameras[c].camera_name == camera_to_render) {
                camera.camera_name;
                break;
            }
        }
        renderSceneThroughFrameBuffer(camera, framebuffer);
    };

    void add_entity(Entity* entity) {
        allEntities[nb_entities] = entity;
        nb_entities++;
    }

    void add_static_camera(mi::StaticCamera static_camera) {
        static_cameras[nb_cameras] = static_camera;
        nb_cameras++;
    }

    void render_all(mi::Vec2 motion, mi::Vec2 camera_rotation) {
        renderEntityFromShaderCode(motion, camera_rotation);
    }
    

    void __MI_ENGINE_BEGUN() {
        depthShader = Shader("shadow/vDepthMap.glsl", "shadow/fDepthMap.glsl", "DEPTH SHADER");
    }
};