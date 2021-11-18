/* 
-- STATIC CAMERA --
The static camera is an unmovable camera used to render scenes to a render texture
*/

namespace mi {

    enum CAMERA_TYPE {
        PERSPECTIVE     = 0x08A,
        ORTHOGRAPHIC    = 0x08B
    };

    class STATICCAMERAPROPERTIES_PERSPECTIVE {
    public:

        float fovdeg;
        float zfar;
        float znear;
        float aspect;

        Vec3 position;
        Vec3 look_target;
        Vec3 local_up;

        STATICCAMERAPROPERTIES_PERSPECTIVE() {}

        STATICCAMERAPROPERTIES_PERSPECTIVE(float fovdeg     = 90.0, 
                                           float aspect     = 1.0, 
                                           float zfar       = 1000.0, 
                                           float znear      = 0.0, 
                                           Vec3 position    = Vec3(10.0), 
                                           Vec3 look_target = Vec3(), 
                                           Vec3 local_up    = Vec3(0.0, 1.0, 0.0)) {
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

        Vec3 position;
        Vec3 look_target;
        Vec3 local_up;

        STATICCAMERAPROPERTIES_ORTHOGRAPHIC(float left              = -50.0, 
                                            float right             =  50.0, 
                                            float top               =  50.0, 
                                            float bottom            = -50.0,
                                            float zfar              = 6000.0,
                                            float znear             = 0.1,
                                            Vec3 position           = Vec3(100.0, 150.0, 50.0), 
                                            Vec3 look_target        = Vec3(0.0), 
                                            Vec3 local_up           = Vec3(0.0, 1.0, 0.0)) {

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
    public:

        Vec3 position;

        CAMERA_TYPE type;
        Matr4 projection;
        Matr4 view;

        std::string camera_name;
        bool isActive = true;

        StaticCamera() {}

        StaticCamera(STATICCAMERAPROPERTIES_ORTHOGRAPHIC orthographic_prop, std::string name) {
            
            camera_name = name;
            type = ORTHOGRAPHIC;

            projection = orthographic(orthographic_prop.left, 
                                      orthographic_prop.right, 
                                      orthographic_prop.bottom, 
                                      orthographic_prop.top,
                                      orthographic_prop.zfar,
                                      orthographic_prop.znear);

            view = lookat(orthographic_prop.position, orthographic_prop.look_target, orthographic_prop.local_up);
            position = orthographic_prop.position;
        }

        StaticCamera(STATICCAMERAPROPERTIES_PERSPECTIVE perspective_prop, std::string name) {

            camera_name = name;
            type = PERSPECTIVE;

            projection = perspective(
                perspective_prop.fovdeg,
                perspective_prop.aspect,
                perspective_prop.zfar,
                perspective_prop.znear);
            
            view = lookat(perspective_prop.position, perspective_prop.look_target, perspective_prop.local_up);
            position = perspective_prop.position;
        }
    };
}