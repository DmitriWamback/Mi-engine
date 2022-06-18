namespace Mi {

    class Transform {
    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        glm::mat4 CreateModel() {
            glm::mat4 s = glm::scale(glm::mat4(1.f), scale / 2.0f);
            glm::mat4 t = glm::translate(glm::mat4(1.f), position);
            glm::mat4 r = MiGLM::eulerAngles(rotation);
            return t * s * r;
        }
    };

    class RenderCollection {
    public:
        std::string name;
        Mi::RRenderer* renderer;

        std::map<std::string, Transform> transformations;
        std::vector<std::string> t_names;
        uint32_t vao;
        uint32_t vertexbuf;
        uint32_t transforms;
        uint32_t opacity;

        static RenderCollection Create() {

            RenderCollection collection = RenderCollection();
            return RenderCollection();
        }

        void SetRenderer(Mi::RRenderer* renderer) {
            this->renderer = renderer;
        }

        void AddTransformation(Transform transform, std::string name) {
            transformations[name] = transform;
            t_names.push_back(name);
        }

        void LinkTransformations() {

        }
    };

    class InstancedRenderer: Mi::Renderer {
    public:

        std::vector<glm::mat4> transformations;
        uint32_t verticesVBO;
        uint32_t transformationsVBO;
        uint32_t vao;
        Mi::Texture tex;
        bool hasTexture;

        std::vector<RenderCollection> renderCollections;

        Mi::RRenderer* base;
        std::string shaderName;
        std::string name;
        bool indexed;

        InstancedRenderer() {}

        static InstancedRenderer Create(Mi::RRenderer* base, bool indexed, std::string name) {

            InstancedRenderer r = InstancedRenderer();

            r.tex = Mi::Texture::Create("src/res/images/grass.png");

            glGenVertexArrays(1, &r.vao);
            glGenBuffers(1, &r.verticesVBO);
            glGenBuffers(1, &r.transformationsVBO);
            r.base = base;
            r.name = name;
            r.indexed = indexed;
            return r;
        }

        void SetTexture(Mi::Texture tex) {
            this->tex = tex;
            hasTexture = true;
        }

        void AddTransformation(glm::vec3 position, glm::vec3 rotation, glm::vec3 size) {
            glm::mat4 model;
            glm::mat4 s = scale(glm::mat4(1.f), size / 2.0f);
            glm::mat4 t = translate(glm::mat4(1.f), position);
            glm::mat4 r = MiGLM::eulerAngles(rotation);
            model = t * s * r;
            transformations.push_back(model);
        }

        void LinkTransformations() {

            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
            glBufferData(GL_ARRAY_BUFFER, base->GetVertexSize() * sizeof(float), base->GetVertices(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);

            glBindBuffer(GL_ARRAY_BUFFER, transformationsVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * transformations.size(), &transformations[0][0], GL_STATIC_DRAW);

            glEnableVertexAttribArray(3);
            glEnableVertexAttribArray(4);
            glEnableVertexAttribArray(5);
            glEnableVertexAttribArray(6);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);

            glBindVertexArray(0);
        }

        void AssignShader(Shader shader) {
            shaderName = shader.shaderName;
        }

        void Render(Shader& shader) {
            //glDisable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            int count = transformations.size();
            int size = base->GetVertexSize() / 8;
            shader.use();
            glBindVertexArray(vao);

            tex.Bind(0);
            glDrawArraysInstanced(RENDER_OPTION, 0, size, count);
            glBindVertexArray(0);
            glEnable(GL_CULL_FACE);
        }
    };
}