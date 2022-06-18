namespace Mi {

    class Material {

        Mi::Shader shader;
        std::string __METALLIC_TEXTURE;
        std::string __ROUGHNESS_TEXTURE;
        std::string __NORMAL_MAP_TEXTURE;

    public:
        float metallic;
        float roughness;

        std::vector<Mi::Texture> textures;

        static Material Create(Mi::Shader shader) {

            Material m = Material();
            m.shader = shader;
            m.metallic = 1.0;
            m.roughness = 1.0;
            return m;
        }

        void Compute(Mi::Camera camera) {

            shader.use();
            shader.setMatr4("projection", camera.projection);
            shader.setMatr4("view", camera.view);
        }
    };
}