namespace Mi {

    class modelbuf {
    public:
        uint32_t vao;
        uint32_t v_vbo;
        uint32_t v_ibo;
        uint32_t u_ibo;
        uint32_t n_ibo;

        modelbuf() {
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &v_vbo); // VBO
            glGenBuffers(1, &v_ibo); // vertex index buffer object
            glGenBuffers(1, &u_ibo); // uv index buffer object
            glGenBuffers(1, &n_ibo); // normal index buffer object
        }
    };

    class Model: public Mi::Inheritable::Entity {
    private:
        int v_index_count;
        int v_count;
        int n_index_count;
        int n_count;
        int u_index_count;
        int u_count;

        const float* vertices;
        const float* normals;
        const float* uvs;
        const uint32_t* v_indices;
        const uint32_t* n_indices;
        const uint32_t* u_indices;
        modelbuf mbuf;

    public:

        Model() {}

        Model(modelbuf buf, const float* vertices, 
                            const float* normals, 
                            const float* uvs,
                            uint32_t* indices, 
                            uint32_t* n_indices, 
                            uint32_t* u_indices,
                            int index_count, 
                            int vertex_count, 
                            int normal_count, 
                            int i_normal_count,
                            int uv_count,
                            int iuv_count) {


            v_index_count = index_count;
            v_count = vertex_count;
            n_index_count = i_normal_count;
            n_count = normal_count;
            u_index_count = iuv_count;
            u_count = uv_count;
            mbuf = buf;

            this->vertices = vertices;
            this->v_indices = indices;
            this->normals = normals;
            this->n_indices = n_indices;
            this->uvs = uvs;
            this->u_indices = u_indices;



            glBindVertexArray(mbuf.vao);

            // LOADING VERTICES
            glBindBuffer(GL_ARRAY_BUFFER, mbuf.v_vbo);
            glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(float), vertices, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mbuf.v_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

            // LOADING NORMALS
            glBufferData(GL_ARRAY_BUFFER, normal_count * sizeof(float), normals, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mbuf.n_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_normal_count * sizeof(uint32_t), n_indices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

            glBufferData(GL_ARRAY_BUFFER, u_count * sizeof(float), uvs, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mbuf.u_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, u_index_count * sizeof(uint32_t), u_indices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

            glBindVertexArray(0);
        }

        void render(Shader &shader) {
            create_model_matrix();
            glm::mat4 model = get_model();
            shader.use();
            shader.setMatr4("model", model);

            glBindVertexArray(mbuf.vao);

            glBindBuffer(GL_ARRAY_BUFFER, mbuf.v_vbo);
            glBufferData(GL_ARRAY_BUFFER, n_count * sizeof(float), normals, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mbuf.n_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_index_count * sizeof(uint32_t), n_indices, GL_STATIC_DRAW);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

            glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(float), vertices, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mbuf.v_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, v_index_count * sizeof(uint32_t), v_indices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

            glDrawElements(RENDER_OPTION, v_index_count, GL_UNSIGNED_INT, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
    };

namespace IO {
    Mi::Inheritable::Entity* LoadModel(const char* file_path, modelbuf buffer) {

        int index_count;
        int vertex_count;

        const float* vertices = load_model_vertices(file_path, &vertex_count, MI_VERTEX);
        uint32_t* indices = load_model_indices(file_path, &index_count, MI_I_VERTEX);

        int normal_count;
        int n_index_count;
        const float* normals = load_model_vertices(file_path, &normal_count, MI_NORMAL);
        uint32_t* n_indices = load_model_indices(file_path, &n_index_count, MI_I_NORMAL);

        int uv_count, uv_index_count;
        const float* uvs = load_model_vertices(file_path, &uv_count, MI_UV);
        uint32_t* iuvs = load_model_indices(file_path, &uv_index_count, MI_I_UV);

        return new Model(buffer, vertices, 
                                 normals,
                                 uvs,
                                 indices, 
                                 n_indices,
                                 iuvs, index_count, vertex_count, normal_count, n_index_count, uv_count, uv_index_count);
    }}
}
