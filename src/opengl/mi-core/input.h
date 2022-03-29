#define GetKeyDown(key) glfwGetKey(main_window, key)
#define GetMouseDown(button) glfwGetMouseButton(main_window, button)

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