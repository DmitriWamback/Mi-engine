/* 
-- CAMERA --
The camera is the main utility to move around within a 3D space
*/

namespace Mi {

    class Camera {

        glm::vec3 up;

    public:

        glm::vec3 position;
        glm::vec3 look_direction;

        glm::mat4 projection;
        glm::mat4 view;
        glm::mat4 lightSpaceMatrix_projection;
        glm::mat4 lightSpaceMatrix_view;

        glm::vec2 rotation;

        float farplane;
        float speed;

        bool isSmooth;
        glm::vec2 direction;
        float t;

        Camera() {
            
            farplane = 1000.f;
            speed = 20.f;
            isSmooth = true;
            t = 1.0f;

            position = glm::vec3(0.0f);
            look_direction = normalize(glm::vec3(-1.0f, -1.0f, -1.0f));
            rotation = glm::vec2(0.0f);
            up = glm::vec3(0.0f, 1.0f, 0.0f);

            projection = glm::perspective(glm::radians(130.0f), 1.0f, 0.1f, farplane);
            view = glm::lookAt(position, position + look_direction, up);
        };

        void rotateCamera(float xdir, float ydir) {
            
            int width, height;
            glfwGetWindowSize(main_window, &width, &height);

            rotation.x -= xdir * 0.25;
            rotation.y += ydir * 0.25;

            if (rotation.y >  89.f) rotation.y =  89.f;
            if (rotation.y < -89.f) rotation.y = -89.f;

            float x_torad = rotation.x / 180.0 * 3.1415926534;
            float y_torad = rotation.y / 180.0 * 3.1415926534;

            look_direction = glm::normalize(glm::vec3(
                cos(y_torad) * cos(x_torad),
                sin(y_torad),
                cos(y_torad) * sin(x_torad)
            ));
        }

        glm::vec3 GetMouseRayNormalized() {
        
            int width, height;
            glfwGetWindowSize(main_window, &width, &height);

            glm::vec2 mouseCoords = glm::vec2(
                ((2*Mi::Input::camera_last_mouse_position.x / (float)width) - 1),
               -((2*Mi::Input::camera_last_mouse_position.y / (float)height) - 1)
            );

            glm::vec4 clipCoords = glm::vec4(mouseCoords, 1.f, 1.f);
            glm::mat4 inv = glm::inverse(projection * glm::lookAt(glm::vec3(0.0f), glm::normalize(look_direction), glm::vec3(0.0f, 1.0f, 0.0f)));
            glm::vec4 r = inv * clipCoords;
            glm::vec3 mouseRay = glm::vec3(r.x, r.y, r.z);

            return glm::normalize(mouseRay);
        }

        void moveCamera(float _speed, glm::vec2 motion) {
            
            glm::vec3 right = glm::normalize(glm::cross(look_direction, up));
            if (motion.x == 0 && motion.y == 0) {
                position += look_direction * direction.x * Mi::Engine::deltaTime * speed * t;
                position += right * direction.y * Mi::Engine::deltaTime * speed * t;
                t -= 0.2;
                if (t <= 0) t = 0;
            }
            else {
                position += look_direction * motion.x * Mi::Engine::deltaTime * speed;
                position += right * motion.y * Mi::Engine::deltaTime * speed;
                t = 1.0;

                direction = motion;
            }

            view = glm::lookAt(position, position + look_direction, up);
        }
    };
}