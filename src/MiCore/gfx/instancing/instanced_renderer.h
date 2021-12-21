namespace mi {

    class InstancedRenderer {
    private:
        std::vector<float> transformations;
        uint32_t verticesVBO;
        uint32_t transformationsVBO;
        uint32_t vao;

    public:
        mi_inheritable::Entity* baseEntity;
        std::string shaderName;
        std::string name;

        InstancedRenderer() {}

        InstancedRenderer(mi_inheritable::Entity* base, std::string name) {
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &verticesVBO);
            glGenBuffers(1, &transformationsVBO);
            baseEntity = base;
            this->name = name;
        }

        void AddTransformation(glm::vec3 position, glm::vec3 rotation, glm::vec3 size) {
            // put transformations into a vector of mi::Vec4 ??
            glm::mat4 model;
            //model = glm::rotate(model, rotation);
        }

        void LinkTransformations() {

            glBindBuffer(GL_ARRAY_BUFFER, transformationsVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * transformations.size() / 16, &transformations[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindVertexArray(vao);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            glEnableVertexAttribArray(3);
            glEnableVertexAttribArray(4);
            glEnableVertexAttribArray(5);
            glEnableVertexAttribArray(6);
            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);

            glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
            glBufferData(GL_ARRAY_BUFFER, baseEntity->get_vertex_length() * sizeof(float), baseEntity->get_vertices(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

            glBindBuffer(GL_ARRAY_BUFFER, transformationsVBO);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), nullptr);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(4 * sizeof(float)));
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(8 * sizeof(float)));
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(12 * sizeof(float)));
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void AssignShader(Shader shader) {
            shaderName = shader.shaderName;
        }

        void Render(Shader& shader) {
            int count = transformations.size() / 16;
            int size = baseEntity->get_vertex_length() / 8;
            shader.use();
            glBindVertexArray(vao);

            glDrawArraysInstanced(RENDER_OPTION, 0, size, count);
            glBindVertexArray(0);
        }
    };
}