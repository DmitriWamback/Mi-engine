namespace Mi {

    class TextRenderer: public Mi::RRenderer {
    public:

        Mi::IO::Font* font;
        Mi::Shader textShader;
        std::string text;
        static glm::vec2 fontSize;
        
        TextRenderer(RenderBuffer buf) {
            
            this->buffer = buf;
            text = "Hello";
            textShader = Mi::Shader::Create("text/vMain.glsl", "text/fMain.glsl", "TEXT_SHADER");

            glBindVertexArray(buffer.VertexArrayObject);
            glBindBuffer(GL_ARRAY_BUFFER, buffer.VertexBufferObject);

            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
            glEnableVertexAttribArray(0);
            glBindVertexArray(0);
        }

        void Update() {
            
            glm::vec2 position = glm::vec2(0.5f);

            textShader.use();
            glBindVertexArray(buffer.VertexArrayObject);
            float xOff = 0.f;
            float width = 0.f;

            for (std::string::const_iterator __it = text.begin(); __it != text.end(); __it++) {
            
                width += font->characters[*__it].bearing.x * fontSize.x + (font->characters[*__it].advance >> 6) * fontSize.x;
            }

            xOff = -width/2.f;
            for (std::string::const_iterator it = text.begin(); it != text.end(); it++) {
            Mi::IO::Character ch = font->characters[*it];

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
            glBindBuffer(GL_ARRAY_BUFFER, buffer.VertexBufferObject);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            xOff += (ch.advance >> 6) * fontSize.x;
        }
        }
    };

    glm::vec2 TextRenderer::fontSize = glm::vec2(0.0008f);
}