namespace Mi {

    class ParticleSystem: public Mi::System {
    public:

        std::function<glm::vec3(float t)> timeFunction;
        glm::vec3 angles;
        float rotationSpeed;
        float speed;
        float max;
        float min;
        Mi::Texture texture;
        Mi::Shader particleShader;

        static ParticleSystem* Create() {

            ParticleSystem* p = new ParticleSystem();
            
            //p->particleShader = Mi::Shader::Create();
            return p;
        }

        void SetTimeFunction(std::function<glm::vec3(float t)> time_func) {
            timeFunction = time_func;
        }
    };
}