namespace mi {

    class InstancedRenderer {
    private:
        std::vector<glm::mat4> transformations;
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
            glm::mat4 model;
            model = glm::translate(glm::mat4(1.0f), position);
            transformations.push_back(model);
        }

        void LinkTransformations() {

            glBindVertexArray(vao);
            std::cout << transformations.size() << std::endl;

            glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
            glBufferData(GL_ARRAY_BUFFER, baseEntity->get_vertex_length() * sizeof(float), baseEntity->get_vertices(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);

            glBindBuffer(GL_ARRAY_BUFFER, transformationsVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * transformations.size(), &transformations[0][0], GL_STATIC_DRAW);
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
            glEnableVertexAttribArray(5);
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
            glEnableVertexAttribArray(6);
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
            int count = transformations.size();
            int size = baseEntity->get_vertex_length() / 8;
            shader.use();
            glBindVertexArray(vao);

            glDrawArraysInstanced(GL_TRIANGLES, 0, size, count);
            glBindVertexArray(0);
        }
    };
}