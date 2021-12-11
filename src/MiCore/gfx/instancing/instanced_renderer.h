namespace mi {

    class InstancedRenderer {
    private:
        std::vector<mi::Vec4> transformations;
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

        void AddTransformation(mi::Vec3 position, mi::Vec3 rotation, mi::Vec3 size) {
            // put transformations into a vector of mi::Vec4 ??
            mi::Matr4 model = rotate(rotation) * scale(size) * translate(position);
            transformations.push_back(model.r1);
            transformations.push_back(model.r2);
            transformations.push_back(model.r3);
            transformations.push_back(model.r4);
        }

        void LinkTransformations() {

            glBindVertexArray(vao);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            glEnableVertexAttribArray(3);
            glEnableVertexAttribArray(4);
            glEnableVertexAttribArray(5);
            glEnableVertexAttribArray(6);

            glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
            glBufferData(GL_ARRAY_BUFFER, baseEntity->get_vertex_length() * sizeof(float), baseEntity->get_vertices(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

            glBindBuffer(GL_ARRAY_BUFFER, transformationsVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(mi::Vec4) * transformations.size(), &transformations[0], GL_STATIC_DRAW);

            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(mi::Vec4), nullptr);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(mi::Vec4), (void*)(1 * sizeof(mi::Vec4)));
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(mi::Vec4), (void*)(2 * sizeof(mi::Vec4)));
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(mi::Vec4), (void*)(3 * sizeof(mi::Vec4)));
            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void AssignShader(Shader shader) {
            shaderName = shader.shaderName;
        }

        void Render(Shader& shader) {
            int count = transformations.size();
            int size = baseEntity->get_vertex_length() / 8;

            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, transformationsVBO);

            glDrawArraysInstanced(RENDER_OPTION, 0, size, count);
            glBindVertexArray(0);
        }
    };
}