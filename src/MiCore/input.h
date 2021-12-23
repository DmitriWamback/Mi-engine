#define GetKeyDown(key) glfwGetKey(main_window, key)
#define GetMouseDown(button) glfwGetMouseButton(main_window, button)

namespace mi_inheritable {
    class Keyboard {
    public:
        virtual void Listen() {}
    };

    class Mouse {
    public:
        virtual void Listen() {}
        virtual glm::vec2 GetMousePosition() {}
    };
}