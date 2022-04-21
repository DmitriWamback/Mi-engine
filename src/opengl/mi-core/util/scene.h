#define __SCENE_MAX_STATIC_CAMERAS 10

/* 
-- SCENE --
The scene is a way to easily organize and render several places
*/

namespace Mi { namespace Inheritable {

    class Scene {
    public: 
    
        std::vector<Mi::InstancedRenderer> renderers;
        std::vector<Mi::UI::UIRenderer> uiRenderers;

        int nb_entities;
        int nb_cameras;

        std::vector<Mi::Renderable> renderableCollection;
        Mi::StaticCamera static_cameras[__SCENE_MAX_STATIC_CAMERAS];

        static Mi::Camera camera;
        Shader depthShader;

        glm::vec3 camera_pos;
        std::string scene_name;

        Scene() {}
    
        Scene(std::string scene_name) {
            this->scene_name = scene_name;
        }

        virtual void MiEngineBegun() {}

        void MoveCamera(glm::vec2 motion, glm::vec2 camera_rotation) {
            camera.rotateCamera(camera_rotation.x, camera_rotation.y);
            camera.moveCamera(1.0, motion);
        }
        
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

        Mi::StaticCamera FindStaticCameraByName(std::string name) {

            Mi::StaticCamera s;

            for (int i = 0; i < nb_cameras; i++) {
                if (static_cameras[i].camera_name == name) s = static_cameras[i];
            }
            return s;
        }

        Mi::InstancedRenderer FindRendererByName(std::string name) {
            for (int i = 0; i < renderers.size(); i++) {
                if (renderers.at(i).name == name) return renderers.at(i);
            }

            std::cout << "Couldn't find Instanced Renderer of name: " << name << ", returning empty IR\n";
            return renderers[0];
        }

        Mi::UI::UIRenderer FindUIRendererByName(std::string name) {
            for (int i = 0; i < uiRenderers.size(); i++) {
                if (uiRenderers.at(i).name == name) return uiRenderers.at(i);
            }
            std::cout << "Couldn't find Ui Renderer of name: " << name << ", returning empty UR\n";
            return uiRenderers[0];
        }

        void AddInstancedRenderer(Mi::InstancedRenderer r) {
            renderers.push_back(r);
        }

        void AddUIRenderer(Mi::UI::UIRenderer renderer) {
            uiRenderers.push_back(renderer);
        }

        void ExportAsJson() {
            
        }

        virtual Mi::RenderTexture LoadSceneThroughFramebuffer(Mi::StaticCamera cam, Mi::Inheritable::Framebuffer* framebuffer, bool includeInstancing) {
            
            glViewport(0, 0, framebuffer->WIDTH, framebuffer->HEIGHT);
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->fbo);
            camera_pos = cam.position;
            
            if (framebuffer->type == Mi::Enum::BUFTYPE_DEPTH) {

                glCullFace(GL_FRONT);
                depthShader.use();
                depthShader.setMatr4("lightSpaceMatrix_projection", cam.projection);
                depthShader.setMatr4("lightSpaceMatrix_view", cam.view);

                camera.lightSpaceMatrix_projection = cam.projection;
                camera.lightSpaceMatrix_view = cam.view;
                glClear(GL_DEPTH_BUFFER_BIT);

                if (includeInstancing) {
                    depthShader.setInt("isInstanced", 1);
                    for (int i = 0; i < renderers.size(); i++) {
                        renderers.at(i).Render(depthShader);
                    }
                }

                depthShader.setInt("isInstanced", 0);
                for (int i = 0; i < nb_entities; i++) {
                    Renderable entity = renderableCollection[i];
                    if (entity.usesDepthBuffer) entity.render(depthShader);
                }
            }
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glCullFace(GL_BACK);

            return Mi::RenderTexture(framebuffer->tex_id);
        }

        void ResetViewport() {
            
            int width;
            int height;
            glfwGetWindowSize(main_window, &width, &height);

#if defined(__APPLE__)

            if (width > height) glViewport(0, -abs(width-height), width*2, width*2);
            else glViewport(-abs(width-height), 0, height*2, height*2);
#else
        
            if (width > height) glViewport(0, -abs(width-height)/2, width, width);
            else glViewport(-abs(width-height)/2, 0, height, height);
#endif
        }

        void MoveEntities() {
            for (int i = 0; i < nb_entities; i++) {
                Mi::Renderable e = renderableCollection[i];
                e.Move();
            }
        }

        void AddEntity(Renderable entity) {
            renderableCollection.push_back(entity);
        }

        void AddStaticCamera(Mi::StaticCamera static_camera) {
            static_cameras[nb_cameras] = static_camera;
            nb_cameras++;
        }

        void RenderAll(glm::vec2 motion, glm::vec2 camera_rotation) {
            SceneMainLoop(motion, camera_rotation);
        }

        void __MI_ENGINE_BEGUN() {
            MiEngineBegun();
            depthShader = Shader::Create("shadow/vDepth.glsl", "shadow/fDepth.glsl", "DEPTH SHADER");
        }
    };

    Mi::Camera Scene::camera = Mi::Camera();
}}