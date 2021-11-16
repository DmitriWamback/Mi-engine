#ifndef MI_VECTOR
    #error "VECTOR CLASS MUST BE INCLUDED"
#else

namespace mi {
    class Matr4 {
    public:
        mi::Vec4 r1, r2, r3, r4;

        Matr4() {};

        Matr4(mi::Vec4 r1, mi::Vec4 r2, mi::Vec4 r3, mi::Vec4 r4) {
            this->r1 = r1;
            this->r2 = r2;
            this->r3 = r3;
            this->r4 = r4;
        }


        Matr4 operator *(mi::Matr4 a) {

            return mi::Matr4(
                mi::Vec4(r1.x * a.r1.x + r1.y * a.r2.x + r1.z * a.r3.x + r1.w * a.r4.x, 
                         r1.x * a.r1.y + r1.y * a.r2.y + r1.z * a.r3.y + r1.w * a.r4.y, 
                         r1.x * a.r1.z + r1.y * a.r2.z + r1.z * a.r3.z + r1.w * a.r4.z, 
                         r1.x * a.r1.w + r1.y * a.r2.w + r1.z * a.r3.w + r1.w * a.r4.w),

                mi::Vec4(r2.x * a.r1.x + r2.y * a.r2.x + r2.z * a.r3.x + r2.w * a.r4.x, 
                         r2.x * a.r1.y + r2.y * a.r2.y + r2.z * a.r3.y + r2.w * a.r4.y, 
                         r2.x * a.r1.z + r2.y * a.r2.z + r2.z * a.r3.z + r2.w * a.r4.z, 
                         r2.x * a.r1.w + r2.y * a.r2.w + r2.z * a.r3.w + r2.w * a.r4.w),

                mi::Vec4(r3.x * a.r1.x + r3.y * a.r2.x + r3.z * a.r3.x + r3.w * a.r4.x, 
                         r3.x * a.r1.y + r3.y * a.r2.y + r3.z * a.r3.y + r3.w * a.r4.y, 
                         r3.x * a.r1.z + r3.y * a.r2.z + r3.z * a.r3.z + r3.w * a.r4.z, 
                         r3.x * a.r1.w + r3.y * a.r2.w + r3.z * a.r3.w + r3.w * a.r4.w),

                mi::Vec4(r4.x * a.r1.x + r4.y * a.r2.x + r4.z * a.r3.x + r4.w * a.r4.x, 
                         r4.x * a.r1.y + r4.y * a.r2.y + r4.z * a.r3.y + r4.w * a.r4.y, 
                         r4.x * a.r1.z + r4.y * a.r2.z + r4.z * a.r3.z + r4.w * a.r4.z, 
                         r4.x * a.r1.w + r4.y * a.r2.w + r4.z * a.r3.w + r4.w * a.r4.w));
        }
    };
}

mi::Matr4 perspective(float fovdeg, float aspect, float zFar, float zNear) {

    float arctanFOV = 1.0 / tan(((fovdeg / 180.0) * 3.14159265) / 2.0);

    return mi::Matr4(
        mi::Vec4(arctanFOV * aspect, 0,                                         0,       0),
        mi::Vec4(0,                  arctanFOV,                                 0,       0),
        mi::Vec4(0,                  0,            -(zFar + zNear)/(zFar - zNear),      -1),
        mi::Vec4(0,                  0,            -(2 * zFar * zNear)/(zFar - zNear),   0)
    );
}

mi::Matr4 translate(mi::Vec3 t) {
    return mi::Matr4(
        mi::Vec4(1,   0,   0,   0),
        mi::Vec4(0,   1,   0,   0),
        mi::Vec4(0,   0,   1,   0),
        mi::Vec4(t.x, t.y, t.z, 1)
    );
}

mi::Matr4 scale(mi::Vec3 s) {
    return mi::Matr4(
        mi::Vec4(s.x, 0,   0,   0),
        mi::Vec4(0,   s.y, 0,   0),
        mi::Vec4(0,   0,   s.z, 0),
        mi::Vec4(0,   0,   0,   1)
    );
}

mi::Matr4 lookat(mi::Vec3 position, mi::Vec3 target, mi::Vec3 up) {

    mi::Vec3 z = normalize(position - target);
    mi::Vec3 x = normalize(cross(up, z));
    mi::Vec3 y = normalize(cross(z, x));

    mi::Vec3 eye = mi::Vec3(
        -dot(x, position),
        -dot(y, position),
        -dot(z, position));

    return mi::Matr4(
        mi::Vec4(x.x,   y.x,   z.x,   0),
        mi::Vec4(x.y,   y.y,   z.y,   0),
        mi::Vec4(x.z,   y.z,   z.z,   0),
        mi::Vec4(eye.x, eye.y, eye.z, 1)
    );
}

mi::Matr4 rotate(mi::Vec3 r_degrees) {
    
    float x_rad = r_degrees.x / 180.0 * 3.14159265;
    float y_rad = r_degrees.y / 180.0 * 3.14159265;
    float z_rad = r_degrees.z / 180.0 * 3.14159265;

    mi::Matr4 x_rot = mi::Matr4(
        mi::Vec4( cos(x_rad), -sin(x_rad),  0,  0),
        mi::Vec4( sin(x_rad),  cos(x_rad),  0,  0),
        mi::Vec4( 0,           0,           1,  0),
        mi::Vec4( 0,           0,           0,  1));

    mi::Matr4 y_rot = mi::Matr4(
        mi::Vec4( cos(y_rad),  0,  sin(y_rad),  0),
        mi::Vec4( 0,           1,  0,           0),
        mi::Vec4(-sin(y_rad),  0,  cos(y_rad),  0),
        mi::Vec4( 0,           0,  0,           1));

    mi::Matr4 z_rot = mi::Matr4(
        mi::Vec4( 1,  0,           0,           0),
        mi::Vec4( 0,  cos(z_rad), -sin(z_rad),  0),
        mi::Vec4( 0,  sin(z_rad),  cos(z_rad),  0),
        mi::Vec4( 0,  0,           0,           1));

    mi::Matr4 rotation_matr = x_rot * y_rot * z_rot;
    return rotation_matr;
}

#endif
