GLenum RENDER_OPTION = GL_TRIANGLES;
GLFWwindow* main_window;

#define LOG_OUT(a) std::cout << a << '\n'
#define WIREFRAME_RENDER_STATE GL_LINES
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

bool isDebugButtonDown;
float biasOffset = 0.0;

namespace mi_input {

    static bool isRightMouseButtonDown;
    glm::vec2 movement_motion(0.0);
    glm::vec2 camera_rotation_movement(0.0);
    static glm::vec2 camera_last_mouse_position(0.0);

    void mouseDown(GLFWwindow* wind, int button, int action, int mod) {

        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) isRightMouseButtonDown = true;
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
            isRightMouseButtonDown = false;
            camera_rotation_movement = glm::vec2(0.0);
        }
    }

    void keyPress() {

        movement_motion = glm::vec2();
        if (glfwGetKey(main_window, GLFW_KEY_W) == GLFW_PRESS) movement_motion.x =  1;
        if (glfwGetKey(main_window, GLFW_KEY_S) == GLFW_PRESS) movement_motion.x = -1;
        if (glfwGetKey(main_window, GLFW_KEY_A) == GLFW_PRESS) movement_motion.y = -1;
        if (glfwGetKey(main_window, GLFW_KEY_D) == GLFW_PRESS) movement_motion.y =  1;
        if (glfwGetKey(main_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) exit(0);

        if (glfwGetKey(main_window, GLFW_KEY_R) == GLFW_PRESS && !isDebugButtonDown) {
            if (RENDER_OPTION == GL_TRIANGLES) RENDER_OPTION = GL_LINES;
            else RENDER_OPTION = GL_TRIANGLES;
            isDebugButtonDown = true;
        }
        if (glfwGetKey(main_window, GLFW_KEY_E) == GLFW_PRESS) {
            biasOffset += 0.01;
            std::cout << biasOffset << std::endl;
        }
        if (glfwGetKey(main_window, GLFW_KEY_Q) == GLFW_PRESS) {
            biasOffset -= 0.01;
            std::cout << biasOffset << std::endl;
        }


        if (glfwGetKey(main_window, GLFW_KEY_R) == GLFW_RELEASE && isDebugButtonDown) {
            isDebugButtonDown = false;
        }
    }

    void mouseMove(GLFWwindow* wind, double xposition, double yposition) {

        if (isRightMouseButtonDown) {
            float x = camera_last_mouse_position.x - xposition;
            float y = camera_last_mouse_position.y - yposition;

            camera_rotation_movement = glm::vec2(x, y);
        }

        camera_last_mouse_position = glm::vec2(xposition, yposition);
    }
}
#include "util/vec_util.h"
#include "util/glm_additions.h"

#include "perlin_noise.h"

#include "gfx/shader.h"
#include "util/renderbuf.h"

#include "entitylib.h"

#include "util/camera.h"
#include "util/static_camera.h"
#include "util/scene.h"

#include "audio/audio_manager.h"
#include "util/mouse.h"

/* 
-- ENGINE --
The engine is a way to communicate to all other files with ease
*/

namespace mi_core {
    std::map<std::string, mi_inheritable::Scene*> scenes;
    std::map<std::string, mi_audio::AudioSource> sources;
}

namespace mi_engine {

    mi_audio::AudioPlayer audioPlayer;

    // Adds a static camera to a given scene
    void MiCoreAddStaticCamera(mi_inheritable::Scene* scene, mi::StaticCamera camera) {
        scene->AddStaticCamera(camera);
    }

    // Assigns an entity a shader to use when being rendered
    void MiCoreEntityAssignShader(mi_inheritable::Entity* entity, Shader shader) {
        entity->shaderToUse = shader.shaderName;
    }

    void MiCoreSceneAddUIRenderer(mi_inheritable::Scene* scene, mi_ui::UIRenderer renderer) {
        scene->AddUIRenderer(renderer);
    }

    void MiCoreEntityAssignWireframeShader(mi_inheritable::Entity* entity, Shader shader) {
        entity->wireframeShaderToUse = shader.shaderName;
    }

    // Adds an audio source to the engine
    void MiCoreAddAudioSource(mi_audio::AudioSource source) {
        mi_core::sources[source.name] = source;
    }

    // Plays a given audio source
    void MiCorePlaySource(std::string source_name) {
        audioPlayer.PlaySound(mi_core::sources[source_name]);
    }
    
    // Stops playing a given audio source
    void MiCoreStopSource(std::string source_name) {
        audioPlayer.StopSound(mi_core::sources[source_name]);
    }

    // Adds a shader to the engine
    void MiCoreAddShader(Shader shader) {
        mi_core::all_shaders[shader.shaderName] = shader;
    }

    // Adds an entity to a scene
    void MiCoreSceneAddEntity(mi_inheritable::Scene* scene, mi_inheritable::Entity* entity) {
        if (mi_core::scenes.find(scene->scene_name) == mi_core::scenes.end()) {
            scene->AddEntity(entity);
            mi_core::scenes[scene->scene_name] = scene;
        }
        else {
            mi_core::scenes[scene->scene_name]->AddEntity(entity);
        }
    }

    void MiCoreSceneAddInstancedRenderer(mi_inheritable::Scene* scene, mi::InstancedRenderer renderer) {
        scene->AddInstancedRenderer(renderer);
    }

    // Runs the engine with a given scene identification
    void MiCoreStartMainLoop(std::string scene_to_render) {
        mi_inheritable::Scene* scene = mi_core::scenes[scene_to_render];

        scene->__MI_ENGINE_BEGUN();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        //glEnable(GL_MULTISAMPLE);  
        //glfwWindowHint(GLFW_SAMPLES, 14);

        while (!glfwWindowShouldClose(main_window)) {

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            mi_input::keyPress();

            glClearColor(0.0, 0.0, 0.0, 0.0);

            scene->RenderAll(mi_input::movement_motion, mi_input::camera_rotation_movement);

            mi_input::camera_rotation_movement = glm::vec2(0.0);
            glfwPollEvents();
            glfwSwapBuffers(main_window);
        }
    }

    // Initializes Mi
    void MiCoreBegin() {
        
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