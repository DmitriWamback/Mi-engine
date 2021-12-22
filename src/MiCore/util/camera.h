/* 
-- CAMERA --
The camera is the main utility to move around within a 3D space
*/

namespace mi {

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

        Camera() {
            position = glm::vec3(0.0, 0.0, 0.0);
            look_direction = normalize(glm::vec3(-1.0, -1.0, -1.0));
            rotation = glm::vec2(0.0);
            up = glm::vec3(0.0, 1.0, 0.0);

            projection = glm::perspective(glm::radians(130.0f), 1.0f, 0.1f, 1000.0f);
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

        glm::vec3 GetMouseRayNormalized(glm::vec2 mousePosition) {
            
            int width, height;
            glfwGetWindowSize(main_window, &width, &height);

            glm::vec2 mouseCoords = glm::vec2(
                (2*mousePosition.x / (float)width) - 1,
               -((2*(mousePosition.y) / (float)height) - 1)
            );

            glm::vec4 clipCoords = glm::vec4(mouseCoords, -1.f, 1.f);
            glm::mat4 invertedProjection = glm::inverse(projection);
            glm::vec4 projectedClipCoords = invertedProjection * clipCoords;
            glm::vec4 eyeSpace = glm::vec4(projectedClipCoords.x, projectedClipCoords.y, -1.f, 0.f);
            glm::mat4 invertedView = glm::inverse(view);
            glm::vec4 ray = invertedView * eyeSpace;
            glm::vec3 mouseRay = glm::vec3(ray.x, ray.y, ray.z);
            return glm::normalize(mouseRay);
        }

        void moveCamera(float speed, glm::vec2 motion) {

            position += look_direction * motion.x;
            glm::vec3 right = glm::normalize(glm::cross(look_direction, up));
            position += right * motion.y;

            view = glm::lookAt(position, position + look_direction, up);
        }
    };
}