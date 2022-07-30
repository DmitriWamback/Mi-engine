#define MATERIAL_ALBEDO_TEXTURE_KEY    "_albedo"
#define MATERIAL_METALLIC_TEXTURE_KEY  "_metallic"
#define MATERIAL_ROUGHNESS_TEXTURE_KEY "_roughness"
#define MATERIAL_NORMAL_MAP_KEY        "_normal"

namespace Mi {

    typedef struct {
        Mi::Shader& shader;
        glm::vec3 color;
        std::map<std::string, Mi::Texture> textures;
        bool illuminate;
    } Material;
}