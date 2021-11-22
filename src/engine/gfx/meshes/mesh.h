namespace mi {

    class Mesh: public Entity {
    public:

        void sync_add_entity(Entity* entity, mi::Vec3 at_position, mi::Vec3 rotation, mi::Vec3 msize) {

        }

        int vertex_count;
        float* all_vertices;
        std::vector<float> debug_vertices;

        Mesh(renderbuf buffer) {
            this->buf = buffer;
            type = mi::MESH;
        }

        void add_entity(Entity* entity, mi::Vec3 at_position, mi::Vec3 rotation, mi::Vec3 msize) {
            float* vertices = entity->get_vertices();
            int size = entity->get_vertex_length();
            vertex_count += size;
            all_vertices = new float[vertex_count];

            //std::thread obj(&mi::Mesh::sync_add_entity, this, entity, at_position, rotation, msize);

            /*
            for (int i = 0; i < size; i++) {
                
                if ((i+8) % 8 == 0)
                    debug_vertices.push_back(vertices[i] * msize.x + at_position.x);
                else if ((i+7) % 8 == 0)
                    debug_vertices.push_back(vertices[i] * msize.y + at_position.y);
                else if ((i+6) % 8 == 0)
                    debug_vertices.push_back(vertices[i] * msize.z + at_position.z);
                else
                    debug_vertices.push_back(vertices[i]);
            }
            for (int i = 0; i < vertex_count; i++) {
                all_vertices[i] = debug_vertices.at(i);
            }

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
            */
        }
    };
    
    class Mesh_ibo: public Entity {

    };
}