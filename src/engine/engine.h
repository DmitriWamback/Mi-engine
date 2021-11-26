GLenum RENDER_OPTION = GL_TRIANGLES;
GLFWwindow* main_window;

#include <thread>
#include "gfx/shader.h"
#include "util/renderbuf.h"

#include "entitylib.h"

#include "gfx/fbo/framebuf.h"
#include "util/camera.h"
#include "util/static_camera.h"
#include "util/scene.h"

/* 
-- ENGINE --
The engine is a way to communicate to all other files with ease
*/

namespace mi_core {
    std::map<std::string, mi_inheritable::Scene*> scenes;
}

bool isDebugButtonDown;

namespace mi_input {

    static bool isRightMouseButtonDown;
    mi::Vec2 movement_motion;
    mi::Vec2 camera_rotation_movement;
    static mi::Vec2 camera_last_mouse_position;

    void mouseDown(GLFWwindow* wind, int button, int action, int mod) {

        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) isRightMouseButtonDown = true;
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
            isRightMouseButtonDown = false;
            camera_rotation_movement = mi::Vec2(0.0);
        }
    }

    void keyPress() {

        movement_motion = mi::Vec2();
        if (glfwGetKey(main_window, GLFW_KEY_W) == GLFW_PRESS) movement_motion.x =  1;
        if (glfwGetKey(main_window, GLFW_KEY_S) == GLFW_PRESS) movement_motion.x = -1;
        if (glfwGetKey(main_window, GLFW_KEY_A) == GLFW_PRESS) movement_motion.y = -1;
        if (glfwGetKey(main_window, GLFW_KEY_D) == GLFW_PRESS) movement_motion.y =  1;

        if (glfwGetKey(main_window, GLFW_KEY_E) == GLFW_PRESS && !isDebugButtonDown) {
            if (RENDER_OPTION == GL_TRIANGLES) RENDER_OPTION = GL_LINE_STRIP;
            else RENDER_OPTION = GL_TRIANGLES;
            isDebugButtonDown = true;
        }
        if (glfwGetKey(main_window, GLFW_KEY_E) == GLFW_RELEASE && isDebugButtonDown) {
            isDebugButtonDown = false;
        }
    }

    void mouseMove(GLFWwindow* wind, double xposition, double yposition) {

        if (isRightMouseButtonDown) {
            float x = camera_last_mouse_position.x - xposition;
            float y = camera_last_mouse_position.y - yposition;

            camera_rotation_movement = mi::Vec2(x, y);
        }

        camera_last_mouse_position = mi::Vec2(xposition, yposition);
    }
}

namespace mi_engine {

    // SEGMENTATION FAULT HERE!!
    void MI_addStaticCamera(mi_inheritable::Scene* scene, mi::StaticCamera camera) {
        scene->add_static_camera(camera);
    }

    void MI_entityAssignShaderCode(mi_inheritable::Entity* entity, Shader shader) {
        entity->shaderToUse = shader.shaderName;
    }

    void MI_addShader(Shader shader) {
        mi_core::all_shaders[shader.shaderName] = shader;
    }

    void MI_sceneAddEntity(mi_inheritable::Scene* scene, mi_inheritable::Entity* entity) {
        if (mi_core::scenes.find(scene->scene_name) == mi_core::scenes.end()) {
            scene->add_entity(entity);
            mi_core::scenes[scene->scene_name] = scene;
        }
        else {
            mi_core::scenes[scene->scene_name]->add_entity(entity);
        }
    }   

    void MI_startMainLoop(std::string scene_to_render) {
        mi_inheritable::Scene* scene = mi_core::scenes[scene_to_render];

        scene->__MI_ENGINE_BEGUN();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        glEnable(GL_MULTISAMPLE);  
        glfwWindowHint(GLFW_SAMPLES, 4);

        while (!glfwWindowShouldClose(main_window)) {

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            mi_input::keyPress();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0, 0.0, 0.0, 1.0);

            scene->render_all(mi_input::movement_motion, mi_input::camera_rotation_movement);

            mi_input::camera_rotation_movement = mi::Vec2(0.0);
            glfwPollEvents();
            glfwSwapBuffers(main_window);
        }
    }

    void __engineBegin() {
        
        if (!glfwInit()) std::cout << "couldn't initialize GLFW\n";

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

        main_window = glfwCreateWindow(1200, 800, "Test", NULL, NULL);
        glfwMakeContextCurrent(main_window);

        glewExperimental = GL_TRUE;
        glewInit();
        glEnable(GL_CULL_FACE);

        glfwSetCursorPosCallback(main_window, mi_input::mouseMove);
        glfwSetMouseButtonCallback(main_window, mi_input::mouseDown);
    }
}