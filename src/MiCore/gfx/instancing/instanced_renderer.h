namespace mi {

    class InstancedRenderer {
    private:
        std::vector<mi::Vec4> transformations;
        uint32_t verticesVBO;
        uint32_t transformationsVBO;

    public:
        mi_inheritable::Entity* baseEntity;

        InstancedRenderer() {}

        InstancedRenderer(mi_inheritable::Entity* base) {
            glGenBuffers(1, &verticesVBO);
            glGenBuffers(1, &transformationsVBO);
            baseEntity = base;
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

            glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(baseEntity->get_vertices()), baseEntity->get_vertices(), GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, transformationsVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(mi::Vec4) * transformations.size(), &transformations[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    };
}