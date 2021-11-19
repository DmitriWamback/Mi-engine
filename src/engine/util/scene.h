#define __SCENE_MAX_ENTITIES 100000
#define __SCENE_MAX_STATIC_CAMERAS 10

/* 
-- SCENE --
The scene is a way to easily organize and render several places
*/

float t = 0;

namespace mi_core {
    std::map<std::string, Shader> all_shaders;
}

class Scene {
private:

    int nb_entities = 0;
    int nb_cameras = 0;

    Entity* allEntities[__SCENE_MAX_ENTITIES];
    mi::StaticCamera static_cameras[__SCENE_MAX_STATIC_CAMERAS];

    mi::Camera camera;
    Shader depthShader;

    mi::Vec3 camera_pos = mi::Vec3();

public:
    std::string scene_name;

    Scene() {}

    Scene(std::string scene_name) {

        this->scene_name = scene_name;
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
            shader.setMatr4("lightSpaceMatrix_projection", camera.lightSpaceMatrix_projection);
            shader.setMatr4("lightSpaceMatrix_view", camera.lightSpaceMatrix_view);
            shader.setVec3("directional_shadow_light_position", camera_pos);
            shader.setInt("main_tex", 1);
            shader.setInt("depthMap", 0);

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

    mi::RenderTexture load_rendered_scene(mi::StaticCamera cam, mi::Framebuffer* framebuffer) {
        
        glViewport(0, 0, framebuffer->WIDTH, framebuffer->HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->fbo);

        mi::Vec3 pos = mi::Vec3(sin(t)*250, 50, cos(t)*250);
        mi::Matr4 v = lookat(pos, mi::Vec3(0.0), mi::Vec3(0.0, 1.0, 0.0));

        cam.position = pos;
        camera_pos = cam.position;
        
        if (framebuffer->type == mi::DEPTH) {
            depthShader.use();
            depthShader.setMatr4("lightSpaceMatrix_projection", cam.projection);
            depthShader.setMatr4("lightSpaceMatrix_view", v);

            camera.lightSpaceMatrix_projection = cam.projection;
            camera.lightSpaceMatrix_view = v;
            glClear(GL_DEPTH_BUFFER_BIT);

            for (int i = 0; i < nb_entities; i++) {
                Entity* entity = allEntities[i];
                entity->render(depthShader);
            }
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        t+=0.01;
        return mi::RenderTexture(framebuffer->tex_id);
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
        depthShader = Shader("shadow/vDepth.glsl", "shadow/fDepth.glsl", "DEPTH SHADER");
    }
};