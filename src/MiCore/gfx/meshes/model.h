namespace mi {

    class Model: public mi_inheritable::Entity {
    private:
        int index_count;
        int vertex_count;

        const float* vertices;
        const uint32_t* indices;

    public:

        Model() {}

        Model(renderbuf buf, const float* vertices, uint32_t* indices, int index_count, int vertex_count) {
            this->index_count = index_count;
            this->vertex_count = vertex_count;
            this->buf = buf;

            this->vertices = vertices;
            this->indices = indices;


            glBindVertexArray(buf.vao);
            glBindBuffer(GL_ARRAY_BUFFER, buf.vbo);
            glBufferData(GL_ARRAY_BUFFER, vertex_count, vertices, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf.ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            glBindVertexArray(0);
        }

        void render(Shader &shader) {
            create_model_matrix();
            Matr4 model = get_model();
            shader.use();
            shader.setMatr4("model", model);

            glBindVertexArray(buf.vao);
            glBindBuffer(GL_ARRAY_BUFFER, buf.vbo);
            glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(float), vertices, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf.ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

            glDrawElements(RENDER_OPTION, index_count, GL_UNSIGNED_INT, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
    };


    mi_inheritable::Entity* LoadModel(const char* file_path, renderbuf buffer) {

        int index_count;
        int vertex_count;

        const float* vertices = load_model_vertices(file_path, &vertex_count);
        uint32_t* indices = load_model_vertex_indices(file_path, &index_count);
        return new Model(buffer, vertices, indices, index_count, vertex_count);
    }
}
