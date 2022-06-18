namespace Mi { namespace UI {
    
    class UIFrame: public Mi::Inheritable::UIElement {
    public:

        UIFrame(glm::vec2 screenPositionPXL, glm::vec2 screenSizePXL) {

            Initialize(screenPositionPXL, screenSizePXL);
            glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);

            glBindVertexArray(0);
        }

        void Render(Shader shader) {
            shader.use();
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    };
}}