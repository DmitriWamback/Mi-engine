namespace mi {
    class PointLight: public mi_inheritable::Light {
    public:

        std::vector<mi::Matr4> views;

        PointLight() {}

        PointLight(mi::Vec3 position) {

        }
    };
}