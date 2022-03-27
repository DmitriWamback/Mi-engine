#define MAX_VERTICES 100000

/* 
-- ENTITY --
The entity is a base class for rendering hard-coded vertex placements
*/


namespace Mi { namespace Enum {
    enum ENTITYTYPE {
        ENT_CUBE = 0, 
        ENT_MESH = 1, 
        ENT_SKYBOX = 2,
        ENT_NOISE_CUBE = 3
    };
}}

namespace Mi { namespace Inheritable {

    class Renderable {
    private:
        glm::mat4 model_matrix;

    public:
        std::string shaderToUse;
        std::string wireframeShaderToUse;
        std::string name;

        bool usesDepthBuffer;
        bool shouldRender;
        float opacity;

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 size;
        glm::vec3 velocity;

        std::vector<Mi::RAttribute> attributes;
        
        renderbuf buf;
        Mi::Enum::ENTITYTYPE type;

        Renderable() {

            shouldRender = true;
            usesDepthBuffer = true;

            position = glm::vec3(0.0);
            rotation = glm::vec3(0.0);
            velocity = glm::vec3(0.0);
            size = glm::vec3(1.0);
        }

        void create_model_matrix() {
            //glm::mat4 r = miGLM::eulerAngles(rotation);
            glm::mat4 s = scale(glm::mat4(1.f), size / 2.0f);
            glm::mat4 t = translate(glm::mat4(1.f), position);
            model_matrix = t * s;
        }

        glm::mat4 get_model() {
            return model_matrix;
        }

        virtual void render(Mi::Shader &shader) {
            shader.use();
            //model_matrix = scale(glm::vec3(1.0));
            //shader.setMatr4("model", model_matrix);
        }

        void Move() {
            position += velocity;
        }

        virtual void renderWithWireFrame(Mi::Shader &mainShader, Mi::Shader &wireframeShader) {}

        virtual float* get_vertices() { return nullptr; }
        virtual int get_vertex_length() { return 0; }
        virtual void initialize() {}
    };
}}