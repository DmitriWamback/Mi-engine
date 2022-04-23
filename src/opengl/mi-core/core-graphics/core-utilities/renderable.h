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

namespace Mi {

    class Renderable {
    private:
        glm::mat4 model_matrix;

    public:
        std::string shaderName;
        std::string wireframeShaderToUse;
        std::string name;

        bool usesDepthBuffer;
        bool shouldRender;
        float opacity;

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 size;
        glm::vec3 velocity;

        std::vector<Mi::RRenderer*>  renderers;
        std::vector<Mi::RAttribute*> attributes;
        
        Mi::Enum::ENTITYTYPE type;

        static Renderable Create() {

            Renderable tempRenderable;
            tempRenderable.shouldRender = true;
            tempRenderable.usesDepthBuffer = true;
            tempRenderable.position = glm::vec3(1.0f);
            tempRenderable.rotation = glm::vec3(0.0f);
            tempRenderable.velocity = glm::vec3(0.0f);
            tempRenderable.size = glm::vec3(1.0f);

            return tempRenderable;
        }

        void create_model_matrix() {
            //glm::mat4 r = miGLM::eulerAngles(rotation);
            glm::mat4 s = scale(glm::mat4(1.f), size / 2.0f);
            glm::mat4 t = translate(glm::mat4(1.f), position);
            glm::mat4 r = MiGLM::eulerAngles(rotation);
            model_matrix = t * s * r;
        }

        template<class T>
        T GetAttributeOfType() {
            for (int i = 0; i < attributes.size(); i++) {
                if (dynamic_cast<T>(attributes[i])) {

                }
            }
        }

        template<class T>
        T TryGetRenderer() {
            try {
                for (int i = 0; i < renderers.size(); i++) {
                    if (dynamic_cast<T>(renderers[i])) {
                        return dynamic_cast<T>(renderers[i]);
                    }
                }
            }
            catch (std::exception& e) {}
            return nullptr;
        }

        void AttachRenderer(Mi::RRenderer* attrib) {
            renderers.push_back(attrib);
        }

        void AttachAttribute(Mi::RAttribute* attrib) {
            attributes.push_back(attrib);
        }

        void render(Mi::Shader &shader) {
            create_model_matrix();
            shader.use();
            shader.setMatr4("model", model_matrix);
            for (int i = 0; i < attributes.size(); i++) attributes[i]->__ATTRUPDATE(shader);
            for (int i = 0; i < renderers.size(); i++) renderers[i]->__ATTRUPDATE(shader);
        }

        void Move() {
            position += velocity;
        }

        virtual void renderWithWireFrame(Mi::Shader &mainShader, Mi::Shader &wireframeShader) {}

        virtual float* get_vertices() { return nullptr; }
        virtual int get_vertex_length() { return 0; }
        virtual void initialize() {}
    };
}