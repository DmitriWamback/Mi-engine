namespace mi {

    class Mesh: public mi_inheritable::Entity {
    public:

        void sync_add_entity(mi_inheritable::Entity* entity, mi::Vec3 at_position, mi::Vec3 rotation, mi::Vec3 msize) {

        }

        int vertex_count;
        float* all_vertices;
        std::vector<float> debug_vertices;

        Mesh(renderbuf buffer) {
            vertex_count = 0;
            this->buf = buffer;
            type = mi_enum::ENT_MESH;
        }

        void add_entity(mi_inheritable::Entity* entity) {
            float* vertices = entity->get_vertices();
            int size = entity->get_vertex_length();
            vertex_count += size;
            
            for (int i = 0; i < size; i++) {
                if ((i+8) % 8 == 0)
                    debug_vertices.push_back(vertices[i] * entity->size.x/2.0 + entity->position.x);
                else if ((i+7) % 8 == 0)
                    debug_vertices.push_back(vertices[i] * entity->size.y/2.0 + entity->position.y);
                else if ((i+6) % 8 == 0)
                    debug_vertices.push_back(vertices[i] * entity->size.z/2.0 + entity->position.z);
                else
                    debug_vertices.push_back(vertices[i]);
            }
        }

        void initialize() {
            all_vertices = &debug_vertices[0];
            glBindVertexArray(buf.vao);
            glBindBuffer(GL_ARRAY_BUFFER, buf.vbo);
            glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(float), all_vertices, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), NULL);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glBindVertexArray(0);
        }

        void render(Shader &shader) {
            shader.use();
            mi::Matr4 model = scale(mi::Vec3(1.0));

            shader.setMatr4("model", model);

            glBindVertexArray(buf.vao);
            glDrawArrays(RENDER_OPTION, 0, vertex_count / 8);
            glBindVertexArray(0);
        }
    };
    
    class Mesh_ibo: public mi_inheritable::Entity {

    };
}