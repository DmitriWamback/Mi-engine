#include "gfx/shader.h"
#include "util/renderbuf.h"

#include "entitylib.h"

#include "gfx/texture/texture.h"
#include "gfx/fbo/framebuf.h"
#include "util/camera.h"
#include "util/static_camera.h"
#include "util/scene.h"

/* 
-- ENGINE --
The engine is a way to communicate to all other files with ease
*/

namespace mi_core {
    std::map<std::string, Scene> scenes;
}

GLFWwindow* main_window;

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


void MI_addStaticCamera(Scene scene, mi::StaticCamera camera) {
    scene.add_static_camera(camera);
}

void MI_entityAssignShaderCode(Entity* entity, Shader shader) {
    entity->shaderToUse = shader.shaderName;
}

void MI_addShader(Shader shader) {
    mi_core::all_shaders[shader.shaderName] = shader;
}

void MI_sceneAddEntity(Scene scene, Entity* entity) {
    if (mi_core::scenes.find(scene.scene_name) == mi_core::scenes.end()) {
        scene.add_entity(entity);
        mi_core::scenes[scene.scene_name] = scene;
    }
    else {
        mi_core::scenes[scene.scene_name].add_entity(entity);
    }
}   

void MI_startMainLoop(std::string scene_to_render) {
    Scene scene = mi_core::scenes[scene_to_render];

    scene.__MI_ENGINE_BEGUN();

    glEnable(GL_DEPTH_TEST);

    mi::StaticCamera orthographic_camera(mi::STATICCAMERAPROPERTIES_ORTHOGRAPHIC(), "Depth");
    mi::Framebuffer* depth = new mi::Depthbuffer(10000, 10000);

    /* TEXTURE DEFINITION HERE */
    //mi::Texture texture = mi::Texture("/images/hello.png");

    while (!glfwWindowShouldClose(main_window)) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int width;
        int height;

        glfwGetWindowSize(main_window, &width, &height);

        mi_input::keyPress();

        /* ANY MAIN GAME FUNCTIONALITY HERE */
        // GETTING SHADOW DEPTH MAP
        mi::RenderTexture depthMap = scene.load_rendered_scene(orthographic_camera, depth);

#ifdef __APPLE__

        if (width > height) glViewport(0, -abs(width-height), width*2, width*2);
        else glViewport(-abs(width-height), 0, height*2, height*2);
#else
    
        if (width > height) glViewport(0, -abs(width-height)/2, width, width);
        else glViewport(-abs(width-height)/2, 0, height, height);
#endif

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap.tex_id);
        //glActiveTexture(GL_TEXTURE1);
        //glBindTexture(GL_TEXTURE_2D, texture.tex_id);
        scene.render_all(mi_input::movement_motion, mi_input::camera_rotation_movement);
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
    //glEnable(GL_CULL_FACE);

    glfwSetCursorPosCallback(main_window, mi_input::mouseMove);
    glfwSetMouseButtonCallback(main_window, mi_input::mouseDown);
}