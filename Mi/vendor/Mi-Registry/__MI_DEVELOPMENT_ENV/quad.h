namespace __MI_DEVELOPMENT_ENVIRONMENT {

    uint32_t vao;
    uint32_t vbo;

    uint32_t tex;
    Mi::IO::Font* __font;
    glm::vec2 fontSize = glm::vec2(0.0008f);

    void InitQuad(Mi::IO::Font* font) {
        __font = font;

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }

    void RenderQuad(Shader shader, std::string text, glm::vec2 position) {
        shader.use();
    
        glBindVertexArray(vao);

        float xOff = 0.f;
        float width = 0.f;
        float nb = text.length();
        std::cout << nb << '\n';

        for (std::string::const_iterator __it = text.begin(); __it != text.end(); __it++) {
            
            width += __font->characters[*__it].bearing.x * fontSize.x + (__font->characters[*__it].advance >> 6) * fontSize.x;
        }

        xOff = -width/2.f;


        for (std::string::const_iterator it = text.begin(); it != text.end(); it++) {
            Mi::IO::Character ch = __font->characters[*it];

            float xpos = position.x + xOff + ch.bearing.x * fontSize.x;
            float ypos = position.y - (ch.size.y - ch.bearing.y) * fontSize.y;

            float width = ch.size.x * fontSize.x;
            float height = ch.size.y * fontSize.y;

            float vertices[6][4] = {
                { xpos,         ypos + height,   0.0f, 0.0f },            
                { xpos,         ypos,            0.0f, 1.0f },
                { xpos + width, ypos,            1.0f, 1.0f },

                { xpos,         ypos + height,   0.0f, 0.0f },
                { xpos + width, ypos,            1.0f, 1.0f },
                { xpos + width, ypos + height,   1.0f, 0.0f } 
            };

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, ch.texid);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            xOff += (ch.advance >> 6) * fontSize.x;
        }
    }
}