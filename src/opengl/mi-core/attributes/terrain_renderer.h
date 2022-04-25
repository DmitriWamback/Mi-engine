namespace Mi {

    class TerrainRenderer: public Mi::RRenderer {
    public: 
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        static int size;
        static float terrainSize;
        float heights[1000][1000]; // size = 1000 (line 105)

        TerrainRenderer(RenderBuffer buf) {
            this->buffer = buf;


            std::vector<glm::vec3> v;
            std::vector<glm::vec3> n;
            std::vector<glm::vec3> f;

            float seed = std::rand()%1000000;
            LOG_OUT(seed);
            // creating vertices
            for (int x = 0; x < size; x++) {
                for (int z = 0; z < size; z++) {

                    int i = z + x * size;
                    float h = Mi::abs_noise_layer(x/134.f, z/134.f, 2.f, .5f, seed, 10) * 12.f;

                    heights[x][z] = h;

                    v.push_back(glm::vec3(((float)x - size/2) * terrainSize, 
                                          h, 
                                          ((float)z - size/2) * terrainSize));

                    if (x != size - 1 && z != size - 1) {
                        indices.push_back(i);
                        indices.push_back(i + 1);
                        indices.push_back(size + i);

                        indices.push_back(i + 1);
                        indices.push_back(i + size + 1);   
                        indices.push_back(i + size);
                    }
                }
            }

            // creating normal vectors
            for (int i = 0; i < v.size() / 3; i++) {
                
                glm::vec3 v1 = v[indices[i*3]];
                glm::vec3 v2 = v[indices[i*3+1]];
                glm::vec3 v3 = v[indices[i*3+2]];

                glm::vec3 normal1 = Mi::CalculateNormal(v1, v2, v3);
                n.push_back(normal1);
            }

            // combining vertices and normals
            for (int i = 0; i < v.size()/3; i++) {
                f.push_back(v[i*3]);
                f.push_back(n[i]);
                f.push_back(v[i*3+1]);
                f.push_back(n[i]);
                f.push_back(v[i*3+2]);
                f.push_back(n[i]);
            }

            // putting them into a float vector
            for (int i = 0; i < f.size()/2; i++) {
                
                vertices.push_back(f[i*2].x);
                vertices.push_back(f[i*2].y);
                vertices.push_back(f[i*2].z);
                vertices.push_back(f[i*2+1].x);
                vertices.push_back(f[i*2+1].y);
                vertices.push_back(f[i*2+1].z);
                vertices.push_back((f[i*2].x + size/2) / (size * terrainSize));
                vertices.push_back((f[i*2].z + size/2) / (size * terrainSize));
            }

            glBindVertexArray(buffer.VertexArrayObject);
            glBindBuffer(GL_ARRAY_BUFFER, buffer.VertexBufferObject);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.IndexBufferObject);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, (indices.size()-1) * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), NULL);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glBindVertexArray(0);
        }

        float GetHeightAt(glm::vec2 xzPosition) {
            
            float gridSquare = terrainSize;

            float x = xzPosition.x + size/2;
            float z = xzPosition.y + size/2;

            int gridX = (int)floor(x / gridSquare);
            int gridZ = (int)floor(z / gridSquare);

            float xCoord = (fmod(x, gridSquare))/gridSquare;
            float zCoord = (fmod(z, gridSquare))/gridSquare;

            float res = 0;

            if (xCoord <= (1-zCoord)) {
                res =  Mi::BaryCentric(glm::vec3(0, heights[gridX  ][gridZ  ], 0),
                                       glm::vec3(1, heights[gridX+1][gridZ  ], 0),
                                       glm::vec3(0, heights[gridX  ][gridZ+1], 1),
                                       glm::vec2(xCoord, zCoord));
            }
            else {
                res =  Mi::BaryCentric(glm::vec3(1, heights[gridX+1][gridZ  ], 0),
                                       glm::vec3(1, heights[gridX+1][gridZ+1], 1),
                                       glm::vec3(0, heights[gridX  ][gridZ+1], 1),
                                       glm::vec2(xCoord, zCoord));
            }

            return res;
        }
        
        void Update(Mi::Shader& shader) {

            glBindVertexArray(buffer.VertexArrayObject);
            glBindBuffer(GL_ARRAY_BUFFER, buffer.VertexBufferObject);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.IndexBufferObject);
            glDrawElements(Triangle, indices.size() - 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    };

    int TerrainRenderer::size = 1000;
    float TerrainRenderer::terrainSize = 1.f;
}