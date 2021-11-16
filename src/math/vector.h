#ifndef MI_VECTOR
#define MI_VECTOR

namespace mi {

    class Vec2 {
    public:
        float x, y;

        Vec2()                 { x = 0; y = 0; }
        Vec2(float x, float y) { this->x = x; this->y = y; }
        Vec2(float a)          { this->x = a; this->y = a; }

        mi::Vec2 operator +(Vec2 a)     { return mi::Vec2(x + a.x, y + a.y); }
        mi::Vec2 operator +(float a)    { return mi::Vec2(x + a, y + a); }
        void operator +=(Vec2 a)        { x += a.x; y += a.y; }
        void operator +=(float a)       {  x += a; y += a; }
        mi::Vec2 operator -(Vec2 a)     { return mi::Vec2(x - a.x, y - a.y); }
        mi::Vec2 operator -(float a)    { return mi::Vec2(x - a, y - a); }
        void operator -=(Vec2 a)        { x -= a.x; y -= a.y; }
        void operator -=(float a)       { x -= a; y -= a; }
        mi::Vec2 operator *(Vec2 a)     { return mi::Vec2(x * a.x, y * a.y); }
        mi::Vec2 operator *(float a)    { return mi::Vec2(x * a, y * a); }
        void operator *=(Vec2 a)        { x *= a.x; y *= a.y; }
        void operator *=(float a)       { x *= a; y *= a; }
        mi::Vec2 operator /(Vec2 a)     { return mi::Vec2(x / a.x, y / a.y); }
        mi::Vec2 operator /(float a)    { return mi::Vec2(x / a, y / a); }
        void operator /=(Vec2 a)        { x /= a.x; y /= a.y; }
        void operator /=(float a)       { x /= a; y /= a; }
    };

    class Vec3 {
    public:
        float x, y, z;

        Vec3()                          { x = 0; y = 0; z = 0; }
        Vec3(mi::Vec2 a, float z)       { this->x = a.x;    this->y = a.y;  this->z = z; }
        Vec3(float x, float y, float z) { this->x = x;      this->y = y;    this->z = z; }
        Vec3(float a)                   { this->x = a;      this->y = a;    this->z = a; }

        void operator +=(Vec3 a)    { x += a.x; y += a.y; z += a.z; }
        void operator +=(float a)   { x += a; y += a; z += a; } 
        void operator -=(Vec3 a)    { x -= a.x; y -= a.y; z -= a.z; }
        void operator -=(float a)   { x -= a; y -= a; z -= a; }
        void operator *=(Vec3 a)    { x *= a.x; y *= a.y; z *= a.z; }
        void operator *=(float a)   { x *= a; y *= a; z *= a; }
        void operator /=(Vec3 a)    { x /= a.x; y /= a.y; z /= a.z; }
        void operator /=(float a)   { x /= a; y /= a; z /= a; }
        mi::Vec3 operator +(Vec3 a)     { return mi::Vec3(x + a.x, y + a.y, z + a.z); }
        mi::Vec3 operator +(float a)    { return mi::Vec3(x + a, y + a, z + a); }
        mi::Vec3 operator -(Vec3 a)     { return mi::Vec3(x - a.x, y - a.y, z - a.z); }
        mi::Vec3 operator -(float a)    { return mi::Vec3(x - a, y - a, z - a); }
        mi::Vec3 operator *(Vec3 a)     { return mi::Vec3(x * a.x, y * a.y, z * a.z); }
        mi::Vec3 operator *(float a)    { return mi::Vec3(x * a, y * a, z * a); }
        mi::Vec3 operator /(Vec3 a)     { return mi::Vec3(x / a.x, y / a.y, z / a.z); }
        mi::Vec3 operator /(float a)    { return mi::Vec3(x / a, y / a, z / a); }
    };

    class Vec4 {
    public:
        float x, y, z, w;

        Vec4()                                      { x = 0; y = 0; z = 0; w = 0; }
        Vec4(mi::Vec2 a, float z, float w)          { this->x = a.x;    this->y = a.y;  this->z = z; this->w = w; }
        Vec4(mi::Vec2 a, mi::Vec2 b)                { this->x = a.x;    this->y = a.y;  this->z = b.x; this->w = b.y; }
        Vec4(mi::Vec3 a, float w)                   { this->x = a.x;    this->y = a.y;  this->z = a.z; this->w = w; }
        Vec4(float x, float y, float z, float w)    { this->x = x;      this->y = y;    this->z = z; this->w = w; }
        Vec4(float a)                               { this->x = a;      this->y = a;    this->z = a; this->w = a; }

        void operator +=(Vec4 a)    { x += a.x; y += a.y; z += a.z; w += a.w; }
        void operator +=(float a)   { x += a; y += a; z += a; w += a; } 
        void operator -=(Vec4 a)    { x -= a.x; y -= a.y; z -= a.z; w -= a.w; }
        void operator -=(float a)   { x -= a; y -= a; z -= a; w -= a; }
        void operator *=(Vec4 a)    { x *= a.x; y *= a.y; z *= a.z; w *= a.w; }
        void operator *=(float a)   { x *= a; y *= a; z *= a; w *= a; }
        void operator /=(Vec4 a)    { x /= a.x; y /= a.y; z /= a.z; w /= a.w; }
        void operator /=(float a)   { x /= a; y /= a; z /= a; w /= a; }
        mi::Vec4 operator +(Vec4 a)     { return mi::Vec4(x + a.x, y + a.y, z + a.z, w + a.w); }
        mi::Vec4 operator +(float a)    { return mi::Vec4(x + a, y + a, z + a, w + a); }
        mi::Vec4 operator -(Vec4 a)     { return mi::Vec4(x - a.x, y - a.y, z - a.z, w - a.w); }
        mi::Vec4 operator -(float a)    { return mi::Vec4(x - a, y - a, z - a, w - a); }
        mi::Vec4 operator *(Vec4 a)     { return mi::Vec4(x * a.x, y * a.y, z * a.z, w * a.w); }
        mi::Vec4 operator *(float a)    { return mi::Vec4(x * a, y * a, z * a, w * a); }
        mi::Vec4 operator /(Vec4 a)     { return mi::Vec4(x / a.x, y / a.y, z / a.z, w / a.w); }
        mi::Vec4 operator /(float a)    { return mi::Vec4(x / a, y / a, z / a, w / a); }
    };
}

void normalize(mi::Vec4& a) {

    float len = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2) + pow(a.w, 2));
    a.x = a.x / len;
    a.y = a.y / len;
    a.z = a.z / len;
    a.w = a.w / len;
}
void normalize(mi::Vec3& a) {
    
    float len = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
    a.x = a.x / len;
    a.y = a.y / len;
    a.z = a.z / len;
}
void normalize(mi::Vec2& a) {
    
    float len = sqrt(pow(a.x, 2) + pow(a.y, 2));
    a.x = a.x / len;
    a.y = a.y / len;
}

mi::Vec4 normalize(mi::Vec4 a) {

    float len = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2) + pow(a.w, 2));
    return mi::Vec4(a.x / len, a.y / len, a.z / len, a.w / len);
}
mi::Vec3 normalize(mi::Vec3 a) {
    
    float len = sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
    return mi::Vec3(a.x / len, a.y / len, a.z / len);
}
mi::Vec2 normalize(mi::Vec2 a) {
    
    float len = sqrt(pow(a.x, 2) + pow(a.y, 2));
    return mi::Vec2(a.x / len, a.y / len);
}

mi::Vec3 cross(mi::Vec3 a, mi::Vec3 b) {
    return mi::Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

float dot(mi::Vec4 a, mi::Vec4 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
float dot(mi::Vec3 a, mi::Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
float dot(mi::Vec2 a, mi::Vec2 b) {
    return a.x * b.x + a.y * b.y;
}

#endif