namespace mi {

    class modelbuf {
    public:
        uint32_t vao;
        uint32_t v_vbo;
        uint32_t v_ibo;

        uint32_t n_vbo;
        uint32_t n_ibo;

        modelbuf() {
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &v_vbo);
            glGenBuffers(1, &v_ibo);
            glGenBuffers(1, &n_vbo);
            glGenBuffers(1, &n_ibo);
        }
    };

    class Model: public mi_inheritable::Entity {
    private:
        int v_index_count;
        int v_count;
        int n_index_count;
        int n_count;

        const float* vertices;
        const float* normals;
        const uint32_t* v_indices;
        const uint32_t* n_indices;
        modelbuf mbuf;

    public:

        Model() {}

        Model(modelbuf buf, const float* vertices, uint32_t* indices, const float* normals, uint32_t* n_indices, 
                             int index_count, int vertex_count, int normal_count, int i_normal_count) {
            v_index_count = index_count;
            v_count = vertex_count;
            mbuf = buf;

            this->vertices = vertices;
            this->v_indices = indices;
            this->normals = normals;
            this->n_indices = n_indices;
            n_index_count = i_normal_count;
            n_count = normal_count;


            glBindVertexArray(mbuf.vao);

            // LOADING VERTICES
            glBindBuffer(GL_ARRAY_BUFFER, mbuf.v_vbo);
            glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(float), vertices, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mbuf.v_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);

            // LOADING NORMALS
            glBindBuffer(GL_ARRAY_BUFFER, mbuf.n_vbo);
            glBufferData(GL_ARRAY_BUFFER, normal_count * sizeof(float), normals, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mbuf.n_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_normal_count * sizeof(uint32_t), n_indices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

            glBindVertexArray(0);
        }

        void render(Shader &shader) {
            create_model_matrix();
            Matr4 model = get_model();
            shader.use();
            shader.setMatr4("model", model);

            glBindVertexArray(mbuf.vao);

            glBindBuffer(GL_ARRAY_BUFFER, mbuf.n_vbo);
            glBufferData(GL_ARRAY_BUFFER, n_count * sizeof(float), normals, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mbuf.n_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_index_count * sizeof(uint32_t), n_indices, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, mbuf.v_vbo);
            glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(float), vertices, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mbuf.v_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, v_index_count * sizeof(uint32_t), v_indices, GL_STATIC_DRAW);

            glDrawElements(RENDER_OPTION, v_index_count, GL_UNSIGNED_INT, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void renderWithWireFrame(Shader &shader, Shader &wireframeShader) {

            shader.use();
            create_model_matrix();
            mi::Matr4 model = get_model();
            shader.setMatr4("model", model);
            glBindVertexArray(mbuf.vao);

            glBindBuffer(GL_ARRAY_BUFFER, mbuf.n_vbo);
            glBufferData(GL_ARRAY_BUFFER, n_count * sizeof(float), normals, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mbuf.n_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_index_count * sizeof(uint32_t), n_indices, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, mbuf.v_vbo);
            glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(float), vertices, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mbuf.v_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, v_index_count * sizeof(uint32_t), v_indices, GL_STATIC_DRAW);

            glDrawElements(RENDER_OPTION, v_index_count, GL_UNSIGNED_INT, 0);

            wireframeShader.use();
            wireframeShader.setMatr4("model", model);
            glDrawElements(WIREFRAME_RENDER_STATE, v_index_count, GL_UNSIGNED_INT, 0);

            glBindVertexArray(0);
        }
    };


    mi_inheritable::Entity* LoadModel(const char* file_path, modelbuf buffer) {

        int index_count;
        int vertex_count;

        const float* vertices = load_model_vertices(file_path, &vertex_count, MI_VERTEX);
        uint32_t* indices = load_model_indices(file_path, &index_count, MI_I_VERTEX);

        int normal_count;
        int n_index_count;
        const float* normals = load_model_vertices(file_path, &normal_count, MI_NORMAL);
        uint32_t* n_indices = load_model_indices(file_path, &n_index_count, MI_I_NORMAL);

        return new Model(buffer, vertices, indices, normals, n_indices, index_count, vertex_count, normal_count, n_index_count);
    }
}
