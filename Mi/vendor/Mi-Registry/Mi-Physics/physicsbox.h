#if defined(MI_ENGINE_OPENGL) && defined(MI_LIBRARIES_LOADED)

enum PHYSICSBOX {
    NON_INDEXED,
    INDEXED
};

class PhysicsBox {
private:
    PHYSICSBOX boxtype;

public:
    glm::vec3 bounds = glm::vec3(1.0);
    std::vector<glm::vec3> vertices;
    std::vector<uint32_t> indices;

    PhysicsBox(std::vector<glm::vec3> vertices) {
        this->boxtype = NON_INDEXED;
        this->vertices = vertices;
    }

    PhysicsBox(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices) {

        this->vertices = vertices;
        this->indices = indices;
        this->boxtype = INDEXED;
    }

    static PhysicsBox* Create(Mi::Inheritable::Renderable* entity) {
        int ATTRIB_LENGTH = 8;
        int VERTEX_LENGTH = 3;
        int arrsize = entity->get_vertex_length() / ATTRIB_LENGTH;

        std::vector<glm::vec3> m_vertices;

        for (int i = 0; i < arrsize; i++) {
            int start_index = i * ATTRIB_LENGTH;

            float x = entity->get_vertices()[start_index],
                  y = entity->get_vertices()[start_index + 1],
                  z = entity->get_vertices()[start_index + 2];

            glm::mat4 s = scale(glm::mat4(1.f), entity->size / 2.0f);
            glm::mat4 t = translate(glm::mat4(1.f), entity->position);
            glm::mat4 model = t * s;

            glm::vec4 worldCoords = model * glm::vec4(glm::vec3(x, y, z), 1.0);
            glm::vec3 worldCoordsxyz = glm::vec3(worldCoords.x, worldCoords.y, worldCoords.z);

            m_vertices.push_back(worldCoordsxyz);
        }

        return new PhysicsBox(m_vertices);
    }

    static PhysicsBox* CreateIndexed(Mi::Inheritable::Renderable* entity) {

    }
};

#endif