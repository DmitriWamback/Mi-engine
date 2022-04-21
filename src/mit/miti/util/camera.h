namespace MITI {

    class Camera {
    public:

        glm::vec3 target;
        glm::mat4 projection;
        glm::mat4 view;
        glm::vec3 position;
        glm::vec3 offset;

        static Camera Create() {

            Camera c = Camera();
            c.target = glm::vec3(0.f);
            c.position = glm::vec3(0.f, 0.f, 0.f);
            c.projection = glm::perspective(glm::radians(90.f), 1.0f, 0.1f, 1000.f);
            c.offset = glm::vec3(0.f);
            return c;
        }

        void UpdateZoom(double amount) {
            zoomDistance += amount;
            if (zoomDistance < 1) zoomDistance = 1;
        }

        void Update() {

            position = glm::normalize(position - target) * zoomDistance;
            double xMouse;
            double yMouse;
            GetMousePosition(&xMouse, &yMouse);

            int width;
            int height;
            glfwGetWindowSize(main_window, &width, &height);

            float xLocalized = (float) (2*(xMouse/(double)width)  - 1.0);
            float yLocalized = (float)-(2*(yMouse/(double)height) - 1.0);
            glm::vec2 current = glm::vec2(xLocalized, yLocalized);

            glm::vec3 right = glm::normalize(glm::cross(glm::normalize(position - target), glm::vec3(0.f, 1.f, 0.f)));
            glm::vec3 dir = -glm::normalize(position - target);
            glm::vec3 tdir = glm::normalize(glm::vec3(dir.x, 0.0, dir.z));

            if (GetKeyDown(GLFW_KEY_A)) offset += right * zoomDistance/50.f;
            if (GetKeyDown(GLFW_KEY_D)) offset -= right * zoomDistance/50.f;

            if (GetKeyDown(GLFW_KEY_W)) offset += tdir * zoomDistance/50.f;
            if (GetKeyDown(GLFW_KEY_S)) offset -= tdir * zoomDistance/50.f;

            if (GetMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                glm::vec2 d = current - lastMousePosition;
                float xDifference = d.x;
                float yDifference = d.y;

                xRotation -= xDifference * 2.f;
                yRotation -= yDifference * 2.f;

                if (yRotation >  1.54362f)  yRotation =  1.54362f;
                if (yRotation < -1.54362f)  yRotation = -1.54362f;

                float xPosition = sin(xRotation) * cos(yRotation);
                float yPosition = sin(yRotation);
                float zPosition = cos(xRotation) * cos(yRotation);
                position = glm::normalize(glm::vec3(xPosition, yPosition, zPosition)) * zoomDistance;
            }
            view = glm::lookAt(position + offset, target + offset, glm::vec3(0.f, 1.f, 0.f));
            lastMousePosition = current;
        }

    private:
        static glm::vec2    lastMousePosition;
        static float        zoomDistance;
        static float        xRotation;
        static float        yRotation;
    };
}

float MITI::Camera::zoomDistance = 132.f;
float MITI::Camera::xRotation = 0.f;
float MITI::Camera::yRotation = 0.f;
glm::vec2 MITI::Camera::lastMousePosition = glm::vec2(0.f);