namespace Mi {
    class PointLight: public Mi::Inheritable::Light {
    private:

    public:
        std::vector<glm::mat4> views;

        PointLight() {}

        PointLight(glm::vec3 position, int resolution) {

            this->position = position;
            views.push_back(glm::lookAt(this->position, this->position + glm::vec3( 1.0,  0.0,  0.0), glm::vec3(0.0, -1.0, 0.0)));
            views.push_back(glm::lookAt(this->position, this->position + glm::vec3(-1.0,  0.0,  0.0), glm::vec3(0.0, -1.0, 0.0)));
            views.push_back(glm::lookAt(this->position, this->position + glm::vec3( 0.0,  1.0,  0.0), glm::vec3(0.0,  0.0, 1.0)));
            views.push_back(glm::lookAt(this->position, this->position + glm::vec3( 0.0, -1.0,  0.0), glm::vec3(0.0,  0.0,-1.0)));
            views.push_back(glm::lookAt(this->position, this->position + glm::vec3( 0.0,  0.0,  1.0), glm::vec3(0.0, -1.0, 0.0)));
            views.push_back(glm::lookAt(this->position, this->position + glm::vec3( 0.0,  0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));
        }
    };
}