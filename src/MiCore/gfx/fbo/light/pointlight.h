namespace mi {
    class PointLight: public mi_inheritable::Light {
    public:

        std::vector<glm::mat4> views;

        PointLight() {}

        PointLight(glm::vec3 position) {

        }
    };
}