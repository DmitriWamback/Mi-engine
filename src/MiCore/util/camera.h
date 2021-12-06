/* 
-- CAMERA --
The camera is the main utility to move around within a 3D space
*/

namespace mi {

    class Camera {

        mi::Vec3 up;

    public:

        mi::Vec3 position;
        mi::Vec3 look_direction;

        mi::Matr4 projection;
        mi::Matr4 view;
        mi::Matr4 lightSpaceMatrix_projection;
        mi::Matr4 lightSpaceMatrix_view;

        mi::Vec2 rotation;

        Camera() {
            position = mi::Vec3(0.0, 0.0, 0.0);
            look_direction = normalize(mi::Vec3(-1.0, -1.0, -1.0));
            rotation = mi::Vec2();
            up = mi::Vec3(0.0, 1.0, 0.0);

            projection = perspective(110.0, 1.0, 1000.0, 0.1);
            view = lookat(position, position + look_direction, up);
        };

        void rotateCamera(float xdir, float ydir) {
            
            rotation.x -= xdir * 0.25;
            rotation.y += ydir * 0.25;

            if (rotation.y >  89.f) rotation.y =  89.f;
            if (rotation.y < -89.f) rotation.y = -89.f;

            float x_torad = rotation.x / 180.0 * 3.1415926534;
            float y_torad = rotation.y / 180.0 * 3.1415926534;

            look_direction = normalize(mi::Vec3(
                cos(y_torad) * cos(x_torad),
                sin(y_torad),
                cos(y_torad) * sin(x_torad)
            ));
        }

        void moveCamera(float speed, mi::Vec2 motion) {

            position += look_direction * motion.x;
            mi::Vec3 right = normalize(cross(look_direction, up));
            position += right * motion.y;

            view = lookat(position, position + look_direction, up);
        }
    };
}