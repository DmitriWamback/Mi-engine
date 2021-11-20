class Cube: public Entity {
public:

    float vertices[288] = {
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


    Cube(renderbuf buffer) {
        this->buf = buffer;

        glBindVertexArray(buf.vao);
        glBindBuffer(GL_ARRAY_BUFFER, buf.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

        create_model_matrix();
        mi::Matr4 model = get_model();

        shader.setMatr4("model", model);

        glBindVertexArray(buf.vao);
        glDrawArrays(RENDER_OPTION, 0, 36);
        glBindVertexArray(0);
    }
};