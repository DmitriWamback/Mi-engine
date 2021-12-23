#define GetKeyDown(key) glfwGetKey(main_window, key)
#define GetMouseDown(button) glfwGetMouseButton(main_window, button)

namespace mi_inheritable {
    class Keyboard {
    public:
        mi_inheritable::Scene* scene;
        Keyboard() {}
        Keyboard(mi_inheritable::Scene* scene) { this->scene = scene; }

        virtual void Listen() {}
    };

    class Mouse {
    public:
        virtual void Listen() {}
        virtual glm::vec2 GetMousePosition() { return glm::vec2(0.0); }
    };
}