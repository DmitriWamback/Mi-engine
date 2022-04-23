namespace Mi {

    class CubeRenderer: public Mi::RRenderer {
    private:
        static float vertices[288];

    public:

        CubeRenderer(RenderBuffer buf) {
            this->buffer = buf;

            glBindVertexArray(buffer.VertexArrayObject);
            glBindBuffer(GL_ARRAY_BUFFER, buffer.VertexBufferObject);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), NULL);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glBindVertexArray(0);
        }

        void Update(Mi::Shader& shader) {
            glBindVertexArray(buffer.VertexArrayObject);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
        }
        
        float* GetVertices() {
            return vertices;
        }

        int GetVertexSize() {
            return sizeof(vertices)/sizeof(vertices[0]);
        }
    };

    float CubeRenderer::vertices[] = {
        -1.0f, -1.0f, -1.0f, /* POSITIONS */  0.0f,  0.0f, -1.0f, /* NORMALS */ 0.0f, 0.0f /* UV COORDS */,
         1.0f,  1.0f, -1.0f,                  0.0f,  0.0f, -1.0f,               1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,                  0.0f,  0.0f, -1.0f,               1.0f, 0.0f,
         1.0f,  1.0f, -1.0f,                  0.0f,  0.0f, -1.0f,               1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,                  0.0f,  0.0f, -1.0f,               0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,                  0.0f,  0.0f, -1.0f,               0.0f, 1.0f,
        
        -1.0f, -1.0f,  1.0f,                  0.0f,  0.0f,  1.0f,               1.0f, 0.0f, 
         1.0f, -1.0f,  1.0f,                  0.0f,  0.0f,  1.0f,               0.0f, 0.0f, 
         1.0f,  1.0f,  1.0f,                  0.0f,  0.0f,  1.0f,               0.0f, 1.0f, 
         1.0f,  1.0f,  1.0f,                  0.0f,  0.0f,  1.0f,               0.0f, 1.0f, 
        -1.0f,  1.0f,  1.0f,                  0.0f,  0.0f,  1.0f,               1.0f, 1.0f, 
        -1.0f, -1.0f,  1.0f,                  0.0f,  0.0f,  1.0f,               1.0f, 0.0f, 
        
        -1.0f,  1.0f,  1.0f,                 -1.0f,  0.0f,  0.0f,               0.0f, 1.0f, 
        -1.0f,  1.0f, -1.0f,                 -1.0f,  0.0f,  0.0f,               1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,                 -1.0f,  0.0f,  0.0f,               1.0f, 0.0f, 
        -1.0f, -1.0f, -1.0f,                 -1.0f,  0.0f,  0.0f,               1.0f, 0.0f, 
        -1.0f, -1.0f,  1.0f,                 -1.0f,  0.0f,  0.0f,               0.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,                 -1.0f,  0.0f,  0.0f,               0.0f, 1.0f, 
        
         1.0f,  1.0f,  1.0f,                  1.0f,  0.0f,  0.0f,               0.0f, 1.0f, 
         1.0f, -1.0f, -1.0f,                  1.0f,  0.0f,  0.0f,               1.0f, 0.0f,
         1.0f,  1.0f, -1.0f,                  1.0f,  0.0f,  0.0f,               1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,                  1.0f,  0.0f,  0.0f,               1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,                  1.0f,  0.0f,  0.0f,               0.0f, 1.0f,
         1.0f, -1.0f,  1.0f,                  1.0f,  0.0f,  0.0f,               0.0f, 0.0f,
        
        -1.0f, -1.0f, -1.0f,                  0.0f, -1.0f,  0.0f,               0.0f, 1.0f,
         1.0f, -1.0f, -1.0f,                  0.0f, -1.0f,  0.0f,               1.0f, 1.0f,
         1.0f, -1.0f,  1.0f,                  0.0f, -1.0f,  0.0f,               1.0f, 0.0f,
         1.0f, -1.0f,  1.0f,                  0.0f, -1.0f,  0.0f,               1.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,                  0.0f, -1.0f,  0.0f,               0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,                  0.0f, -1.0f,  0.0f,               0.0f, 1.0f,
        
        -1.0f,  1.0f, -1.0f,                  0.0f,  1.0f,  0.0f,               0.0f, 1.0f,
         1.0f,  1.0f , 1.0f,                  0.0f,  1.0f,  0.0f,               1.0f, 0.0f,
         1.0f,  1.0f, -1.0f,                  0.0f,  1.0f,  0.0f,               1.0f, 1.0f,
         1.0f,  1.0f,  1.0f,                  0.0f,  1.0f,  0.0f,               1.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,                  0.0f,  1.0f,  0.0f,               0.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,                  0.0f,  1.0f,  0.0f,               0.0f, 0.0f
    };
}