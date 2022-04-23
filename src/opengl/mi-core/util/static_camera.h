/* 
-- STATIC CAMERA --
The static camera is an unmovable camera used to render scenes to a render texture
*/

namespace Mi { namespace Enum {
    enum CAMERA_TYPE {
        PERSPECTIVE     = 0x08A,
        ORTHOGRAPHIC    = 0x08B
    };
}}

namespace Mi {

    class STATICCAMERAPROPERTIES_PERSPECTIVE {
    public:

        float fovdeg;
        float zfar;
        float znear;
        float aspect;

        glm::vec3 position;
        glm::vec3 look_target;
        glm::vec3 local_up;

        STATICCAMERAPROPERTIES_PERSPECTIVE(float fovdeg     = 90.0, 
                                           float aspect     = 1.0, 
                                           float zfar       = 1000.0, 
                                           float znear      = 0.0, 
                                           glm::vec3 position    = glm::vec3(10.0), 
                                           glm::vec3 look_target = glm::vec3(0.0), 
                                           glm::vec3 local_up    = glm::vec3(0.0, 1.0, 0.0)) {
            this->fovdeg = fovdeg;
            this->aspect = aspect;
            this->zfar = zfar;
            this->znear = znear;

            this->position = position;
            this->look_target = look_target;
            this->local_up = local_up;
        }
    };

    class STATICCAMERAPROPERTIES_ORTHOGRAPHIC {
    public:
        float left;
        float right;
        float top;
        float bottom;
        float zfar;
        float znear;

        glm::vec3 position;
        glm::vec3 look_target;
        glm::vec3 local_up;

        STATICCAMERAPROPERTIES_ORTHOGRAPHIC(float left                   = -10.0, 
                                            float right                  =  10.0, 
                                            float top                    =  10.0, 
                                            float bottom                 = -10.0,
                                            float zfar                   =  10000.0,
                                            float znear                  =  0.1,
                                            glm::vec3 position           =  glm::vec3(460.0f, 200.0f, 200.0f), 
                                            glm::vec3 look_target        =  glm::vec3(0.0f), 
                                            glm::vec3 local_up           =  glm::vec3(0.0f, 1.0f, 0.0f)) {

            this->left = left;
            this->right = right;
            this->top = top;
            this->bottom = bottom;
            this->zfar = zfar;
            this->znear = znear;
            this->position = position;
            this->look_target = look_target;
            this->local_up = local_up;
        }
    };
    
    class StaticCamera {
    private:
        glm::vec3 start_position;
        glm::vec3 start_target;

    public:

        glm::vec3 position;
        glm::vec3 target;

        Mi::Enum::CAMERA_TYPE type;
        glm::mat4 projection;
        glm::mat4 view;

        float zfar;
        float znear;

        std::string camera_name;
        bool isActive;

        StaticCamera() {}

        StaticCamera(STATICCAMERAPROPERTIES_ORTHOGRAPHIC orthographic_prop, std::string name) {
            
            isActive = true;
            camera_name = name;
            type = Mi::Enum::ORTHOGRAPHIC;

            projection = glm::ortho(orthographic_prop.left, 
                                    orthographic_prop.right, 
                                   -orthographic_prop.bottom, 
                                   -orthographic_prop.top,
                                    orthographic_prop.znear,
                                    orthographic_prop.zfar);

            view = glm::lookAt(orthographic_prop.position, orthographic_prop.look_target, orthographic_prop.local_up);
            position = orthographic_prop.position;
            target = orthographic_prop.look_target;
            start_position = position;
            start_target = target;

            zfar = orthographic_prop.zfar;
            znear = orthographic_prop.znear;
        }

        StaticCamera(STATICCAMERAPROPERTIES_PERSPECTIVE perspective_prop, std::string name) {

            isActive = true;
            camera_name = name;
            type = Mi::Enum::PERSPECTIVE;

            projection = glm::perspective(
                glm::radians(perspective_prop.fovdeg),
                perspective_prop.aspect,
                perspective_prop.zfar,
                perspective_prop.znear);
            
            view = glm::lookAt(perspective_prop.position, perspective_prop.look_target, perspective_prop.local_up);
            position = perspective_prop.position;
            target = perspective_prop.look_target;
            start_position = position;
            start_target = target;

            zfar = perspective_prop.zfar;
            znear = perspective_prop.znear;
        }

        glm::vec3 GetStartPosition() {
            return start_position;
        }

        glm::vec3 GetStartTarget() {
            return start_target;
        }

        glm::vec3 GetCurrentPosition() {
            return position;
        }

        glm::vec3 GetCurrentTarget() {
            return target;
        }

        void set_position(glm::vec3 position) {
            this->position = position;
            view = glm::lookAt(this->position, this->target, glm::vec3(0.0, 1.0, 0.0));
        }

        void set_target(glm::vec3 target) {
            this->target = target;
            view = glm::lookAt(this->position, this->target, glm::vec3(0.0, 1.0, 0.0));
        }
    };
}