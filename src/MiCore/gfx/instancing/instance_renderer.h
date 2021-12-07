namespace mi {

    class InstancedRenderer {
    private:
        std::vector<mi::Matr4> transformations;
        uint32_t transformationsVBO;

    public:
        mi_inheritable::Entity* baseEntity;

        InstancedRenderer(mi_inheritable::Entity* base) {
            baseEntity = base;
        }

        void AddTransformation(mi::Matr4 matr) {
            transformations.push_back(matr);
        }

        void AddTransformation(mi::Vec3 position, mi::Vec3 rotation, mi::Vec3 size) {
            mi::Matr4 model = rotate(rotation) * scale(size) * translate(position);
            transformations.push_back(model);
        }
    };
}