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

namespace mi_inheritable {

    class Scene {
    public:

        int nb_entities;
        int nb_cameras;

        Entity* allEntities[__SCENE_MAX_ENTITIES];
        mi::StaticCamera static_cameras[__SCENE_MAX_STATIC_CAMERAS];

        mi::Camera camera;
        Shader depthShader;

        mi::Vec3 camera_pos;
        std::string scene_name;

        Scene() {}

        Scene(std::string scene_name) {
            this->scene_name = scene_name;
            nb_entities = 0;
            nb_cameras = 0;
        }

        void move_camera(mi::Vec2 motion, mi::Vec2 camera_rotation) {
            camera.rotateCamera(camera_rotation.x, camera_rotation.y);
            camera.moveCamera(1.0, motion);
        }

        virtual void mi_engine_begun() {}
        
        virtual void SceneMainLoop(mi::Vec2 motion, mi::Vec2 camera_rotation) {}

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

        virtual mi::RenderTexture load_rendered_scene(mi::StaticCamera cam, mi_inheritable::Framebuffer* framebuffer) {
            
            glViewport(0, 0, framebuffer->WIDTH, framebuffer->HEIGHT);
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->fbo);

            //cam.set_position(cam.get_start_position() + mi::Vec3(camera.position.x, 0, camera.position.z));
            //cam.set_target(cam.get_start_target() + mi::Vec3(camera.position.x, 0, camera.position.z));
            camera_pos = cam.position;
            
            if (framebuffer->type == mi_enum::BUFTYPE_DEPTH) {

                glCullFace(GL_FRONT);
                depthShader.use();
                depthShader.setMatr4("lightSpaceMatrix_projection", cam.projection);
                depthShader.setMatr4("lightSpaceMatrix_view", cam.view);

                camera.lightSpaceMatrix_projection = cam.projection;
                camera.lightSpaceMatrix_view = cam.view;
                glClear(GL_DEPTH_BUFFER_BIT);

                for (int i = 0; i < nb_entities; i++) {
                    Entity* entity = allEntities[i];
                    if (entity->usesDepthBuffer) entity->render(depthShader);
                }
            }
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glCullFace(GL_BACK);

            return mi::RenderTexture(framebuffer->tex_id);
        }

        void reset_viewport() {
#ifdef __APPLE__
            int width;
            int height;

            glfwGetWindowSize(main_window, &width, &height);
            
            if (width > height) glViewport(0, -abs(width-height), width*2, width*2);
            else glViewport(-abs(width-height), 0, height*2, height*2);
#else
        
            if (width > height) glViewport(0, -abs(width-height)/2, width, width);
            else glViewport(-abs(width-height)/2, 0, height, height);
#endif
        }

        void add_entity(Entity* entity) {
            allEntities[nb_entities] = entity;
            nb_entities++;
        }

        void add_static_camera(mi::StaticCamera static_camera) {
            std::cout << nb_cameras << " Here" << std::endl;
            static_cameras[nb_cameras] = static_camera;
            nb_cameras++;
        }

        void render_all(mi::Vec2 motion, mi::Vec2 camera_rotation) {
            SceneMainLoop(motion, camera_rotation);
        }
        

        void __MI_ENGINE_BEGUN() {
            mi_engine_begun();
            depthShader = Shader("shadow/vDepth.glsl", "shadow/fDepth.glsl", "DEPTH SHADER");
        }
    };
}