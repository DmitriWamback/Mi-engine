#include "libs.h"
#define MI_ENGINE_OPENGL

#if defined(_WIN32)
    #if defined(_WIN64)
        #define MI_WINDOWS_IMPLEMENTATION
    #else
        #error "Cannot run x86"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #define MI_APPLE_IMPLEMENTATION

#elif defined(__linux__)
    #define MI_LINUX_IMPLEMENTATION

#else
    #error "Unknown platform cannot be supported"
#endif

#include <Mi-Registry/errors.h>

#define KEY_UP                  GLFW_PRESS
#define KEY_DOWN                GLFW_RELEASE
#define MOUSE_BUTTON_RIGHT      GLFW_MOUSE_BUTTON_RIGHT
#define MOUSE_BUTTON_LEFT       GLFW_MOUSE_BUTTON_LEFT

#define GetKeyDown(key)             glfwGetKey(main_window, key) == KEY_UP
#define GetKeyUp(key)               glfwGetKey(main_window, key) == KEY_DOWN
#define GetMouseButtonDown(key)     glfwGetMouseButton(main_window, key) == KEY_UP
#define GetMouseButtonUp(key)       glfwGetMouseButton(main_window, key) == KEY_DOWN

int RENDERABLE_COUNT = 0;
#define __MI_UPDATE_GLOBAL_RENDERABLE_COUNT() RENDERABLE_COUNT++

GLenum RENDER_OPTION = GL_TRIANGLES;
GLFWwindow* main_window;

namespace Mi { namespace Engine {
    float deltaTime;
}}

#define RenderNonIndexed(mode, first, count)            glDrawArrays(mode, first, count)
#define RenderIndexed(mode, count, type, indices)       glDrawElements(mode, first, type, count)
#define Triangle                                        GL_TRIANGLES
#define Wireframe                                       GL_LINES
#define ConnectedWireframe                              GL_LINE_STRIP
#define Point                                           GL_POINTS

void GetMousePosition(double* x, double* y) {
    glfwGetCursorPos(main_window, x, y);
}


#define LOG_OUT(a) std::cout << a << '\n'
#define LOG_OUT2(a, b) std::cout << a << ' ' << b << '\n'
#define LOG_OUT3(a, b, c) std::cout << a << ' ' << b << ' ' << c << '\n'

#define WIREFRAME_RENDER_STATE GL_LINES
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Mi-Registry/Mi-Audio/registry.h>
#include <unordered_map>
#include <ft2build.h>
#include <Mi-Registry/Mi-Font/registry.h>

#include "util/math.h"

bool isDebugButtonDown;
float biasOffset = 0.0;

namespace Mi { namespace Input {

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
}}
#include "util/vec_util.h"
#include "util/glm_additions.h"
#include "perlin_noise.h"
#include <Mi-Registry/Mi-Serial-Communication/registry.h>
#include "core-graphics/shader.h"

namespace Mi { namespace Core {
    std::map<std::string, Mi::Shader> allShaders;
    std::map<std::string, Mi::Hardware::Serialport> ports;
    std::map<std::string, const char*> portMessages;
}
namespace Engine {

    Mi::Shader MiCoreFindShader(std::string name) {
        if (Mi::Core::allShaders.find(name) != Mi::Core::allShaders.end()) {
            return Mi::Core::allShaders[name];
        }

        return Mi::Core::allShaders["STANDARD"];
    }
}}


#include "core-graphics/texture/texture.h"
#include "core-graphics/texture/cubemap.h"
#include <Mi-Registry/Mi-Physics/registry.h>
#include <Mi-Registry/Mi-Post-Processing/registry.h>
#include <Mi-Registry/Mi-Attrib/registry.h>

#include "attributes/cube_renderer.h"
#include "attributes/terrain_renderer.h"
#include "attributes/quad_renderer.h"
#include "attributes/text_renderer.h"

#include "core-graphics/colorbuf/colorbuf.h"
#include "util/camera.h"
#include "entitylib.h"
#include "core-graphics/ui/ui_element.h"
#include "core-graphics/ui/ui_button.h"
#include "core-graphics/ui/ui_frame.h"
#include "core-graphics/ui/ui_renderer.h"
#include "util/static_camera.h"
#include "util/scene.h"
#include "util/mouse.h"
#include "input.h"
#include "util/t_sort.h"
#define MI_LIBRARIES_LOADED
#include <Mi-Registry/Mi-Bindings/resgistry.h>
#include "effects/effects.h"

namespace Mi { namespace Input {

    Mi::Inheritable::Keyboard* subKeyboard = nullptr;
    Mi::Inheritable::Mouse* subMouse = nullptr;
}}

/* 
-- ENGINE --
The engine is a way to communicate to all other files with ease
*/

namespace Mi { namespace Core {
    std::map<std::string, Mi::Inheritable::Scene*> scenes;
    std::map<std::string, Mi::Audio::AudioSource> sources;
}}


namespace Mi { namespace Engine {

    Mi::Audio::AudioPlayer audioPlayer;

    // Adds a static camera to a given scene
    void MiCoreAddStaticCamera(Mi::Inheritable::Scene* scene, Mi::StaticCamera camera) {
        //scene->AddStaticCamera(camera);
    }

    // Adds a serial port for serial communication
    void MiCoreAddSerialPort(Mi::Hardware::Serialport port, std::string name) {
        Mi::Core::ports[name] = port;
    }

    // Assigns an entity a shader to use when being rendered
    void MiCoreEntityAssignShader(Mi::Renderable entity, Mi::Shader shader) {
        entity.shaderName = shader.shaderName;
    }

    void MiCoreSceneAddUIRenderer(Mi::Inheritable::Scene* scene, Mi::UI::UIRenderer renderer) {
        //scene->AddUIRenderer(renderer);
    }

    void MiCoreEntityAssignWireframeShader(Mi::Renderable entity, Mi::Shader shader) {
        entity.wireframeShaderToUse = shader.shaderName;
    }

    // Adds an audio source to the engine
    void MiCoreAddAudioSource(Mi::Audio::AudioSource source) {
        Mi::Core::sources[source.name] = source;
    }

    // Plays a given audio source
    void MiCorePlaySource(std::string source_name) {

    }
    
    // Stops playing a given audio source
    void MiCoreStopSource(std::string source_name) {

    }

    void MiCoreAddScene(Mi::Inheritable::Scene* scene) {
        Mi::Core::scenes[scene->scene_name] = scene;
    }

    // Adds a shader to the engine
    void MiCoreAddShader(Mi::Shader shader) {
        Mi::Core::allShaders[shader.shaderName] = shader;
    }

    // Adds an entity to a scene
    void MiCoreSceneAddEntity(Mi::Inheritable::Scene* scene, Mi::Renderable entity) {
        if (Mi::Core::scenes.find(scene->scene_name) == Mi::Core::scenes.end()) {
            //scene->AddEntity(entity);
            Mi::Core::scenes[scene->scene_name] = scene;
        }
        else {
            //Mi::Core::scenes[scene->scene_name]->AddEntity(entity);
        }
    }

    void MiCoreSceneAddInstancedRenderer(Mi::Inheritable::Scene* scene, Mi::InstancedRenderer renderer) {
        scene->AddInstancedRenderer(renderer);
    }

    void MiCoreSetSubKeyboard(Mi::Inheritable::Keyboard* keyboard) {
        Mi::Input::subKeyboard = keyboard;
    }

    void MiCoreSetSubMouse(Mi::Inheritable::Mouse* mouse) {
        Mi::Input::subMouse = mouse;
    }

    // Runs the engine with a given scene identification
    void MiCoreStartMainLoop(std::string scene_to_render) {
        Mi::Inheritable::Scene* scene = Mi::Core::scenes[scene_to_render];

        scene->__MI_ENGINE_BEGUN();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

        float oldTime = 0;

        while (!glfwWindowShouldClose(main_window)) {

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            Mi::Input::keyPress();

            glClearColor(0.0, 0.0, 0.0, 0.0);

            if (Mi::Input::subKeyboard != nullptr) Mi::Input::subKeyboard->Listen();
            if (Mi::Input::subMouse != nullptr) Mi::Input::subMouse->Listen();

            float currentTime = glfwGetTime();
            deltaTime = currentTime - oldTime;
            oldTime = currentTime;

            scene->RenderAll(Mi::Input::movement_motion, Mi::Input::camera_rotation_movement);

            Mi::Input::camera_rotation_movement = glm::vec2(0.0);
            glfwPollEvents();
            glfwSwapBuffers(main_window);
        }
    }

    // Initializes Mi
    void MiCoreBegin(int width, int height, const char* name) {
        
        if (!glfwInit()) std::cout << "couldn't initialize GLFW\n";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

        glfwWindowHint(GLFW_SAMPLES, 4);
        main_window = glfwCreateWindow(width, height, name, NULL, NULL);
        glfwMakeContextCurrent(main_window);

        glewExperimental = GL_TRUE;
        glewInit();
        glEnable(GL_CULL_FACE);
        glEnable(GL_MULTISAMPLE);

        MiCoreAddShader(Mi::Shader::Create("standard/vMain.glsl", "standard/fMain.glsl", "STANDARD"));  

        glfwSetCursorPosCallback(main_window, Mi::Input::mouseMove);
        glfwSetMouseButtonCallback(main_window, Mi::Input::mouseDown);
    }
}}