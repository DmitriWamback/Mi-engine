#define MOUSE_BUTTON_RIGHT          GLFW_MOUSE_BUTTON_RIGHT
#define MOUSE_BUTTON_LEFT           GLFW_MOUSE_BUTTON_LEFT
#define KEY_UP                      GLFW_PRESS
#define KEY_DOWN                    GLFW_RELEASE

#define GetKeyDown(key)             glfwGetKey(main_window, key) == KEY_UP
#define GetKeyUp(key)               glfwGetKey(main_window, key) == KEY_DOWN
#define GetMouseButtonDown(key)     glfwGetMouseButton(main_window, key) == KEY_UP
#define GetMouseButtonUp(key)       glfwGetMouseButton(main_window, key) == KEY_DOWN

namespace Mi { namespace Inheritable {
    class Keyboard {
    public:
        Mi::Inheritable::Scene* scene;
        Keyboard() {}
        Keyboard(Mi::Inheritable::Scene* scene) { this->scene = scene; }

        virtual void Listen() {}
    };

    class Mouse {
    public:
        virtual void Listen() {}
        virtual glm::vec2 GetMousePosition() { return glm::vec2(0.0); }
    };
}}