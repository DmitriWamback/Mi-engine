#define __SCENE_MAX_ENTITIES 5000000
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

        std::vector<mi::InstancedRenderer> renderers;
        std::vector<mi_ui::UIRenderer> uiRenderers;

        int nb_entities;
        int nb_cameras;

        Entity* allEntities[__SCENE_MAX_ENTITIES];
        mi::StaticCamera static_cameras[__SCENE_MAX_STATIC_CAMERAS];

        mi::Camera camera;
        Shader depthShader;

        glm::vec3 camera_pos;
        std::string scene_name;

        Scene() {}

        Scene(std::string scene_name) {
            this->scene_name = scene_name;
            nb_entities = 0;
            nb_cameras = 0;
        }

        void MoveCamera(glm::vec2 motion, glm::vec2 camera_rotation) {
            camera.rotateCamera(camera_rotation.x, camera_rotation.y);
            camera.moveCamera(1.0, motion);
        }

        void Remove(Entity* e) {
            for (int i = 0; i < nb_entities; i++) {
                if (allEntities[i] == e) allEntities[i] = nullptr;
            }
        }

        virtual void MiEngineBegun() {}
        
        virtual void SceneMainLoop(glm::vec2 motion, glm::vec2 camera_rotation) {}

        glm::vec3 GetCameraPosition() {
            return camera.position;
        }

        glm::vec3 GetCameraLookDirection() {
            return camera.look_direction;
        }

        glm::mat4 GetProjection() {
            return camera.projection;
        }

        glm::mat4 GetView() {
            return camera.view;
        }

        mi::StaticCamera FindStaticCameraByName(std::string name) {
            for (int i = 0; i < nb_cameras; i++) {
                if (static_cameras[i].camera_name == name) return static_cameras[i];
            }
        }

        mi::InstancedRenderer FindRendererByName(std::string name) {
            for (int i = 0; i < renderers.size(); i++) {
                if (renderers.at(i).name == name) return renderers.at(i);
            }
        }

        void AddInstancedRenderer(mi::InstancedRenderer r) {
            renderers.push_back(r);
        }

        void AddUIRenderer(mi_ui::UIRenderer renderer) {
            uiRenderers.push_back(renderer);
        }

        void ExportAsJson() {
            
        }

        virtual mi::RenderTexture LoadSceneThroughFramebuffer(mi::StaticCamera cam, mi_inheritable::Framebuffer* framebuffer) {
            
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
                    if (entity != nullptr) {
                        if (entity->usesDepthBuffer) entity->render(depthShader);
                    }
                }
            }
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glCullFace(GL_FRONT_AND_BACK);

            return mi::RenderTexture(framebuffer->tex_id);
        }

        void ResetViewport() {
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

        void MoveEntities() {
            for (int i = 0; i < nb_entities; i++) {
                mi_inheritable::Entity* e = allEntities[i];
                if (e != nullptr) e->Move();
            }
        }

        void AddEntity(Entity* entity) {
            allEntities[nb_entities] = entity;
            nb_entities++;
        }

        void AddStaticCamera(mi::StaticCamera static_camera) {
            static_cameras[nb_cameras] = static_camera;
            nb_cameras++;
        }

        void RenderAll(glm::vec2 motion, glm::vec2 camera_rotation) {
            SceneMainLoop(motion, camera_rotation);
        }
        

        void __MI_ENGINE_BEGUN() {
            MiEngineBegun();
            depthShader = Shader("shadow/vDepth.glsl", "shadow/fDepth.glsl", "DEPTH SHADER");
        }
    };
}