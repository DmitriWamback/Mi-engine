namespace mi_inheritable {

    class UIElement {
    public:
        glm::vec2 position;
        float rotation;
        glm::vec2 size;
        renderbuf buf;

        float* vertices;

        bool scaleWithScreenSize = false;

        UIElement() {}

        UIElement(renderbuf buffer, glm::vec2 screenPositionPXL, glm::vec2 screenSizePXL) {
            this->buf = buffer;
            Initialize(screenPositionPXL, screenSizePXL);
        }

        virtual void Render(Shader& shader) {

        }

        void Initialize(glm::vec2 screenPositionPXL, glm::vec2 screenSizePXL) {
            int s_width, s_height;
            glfwGetWindowSize(main_window, &s_width, &s_height);

            glm::vec2 localizedPosition = glm::vec2(
                screenPositionPXL.x / s_width,
                screenPositionPXL.y / s_height
            );

            glm::vec2 localizedSize = glm::vec2(
                screenSizePXL.x / s_width,
                screenSizePXL.y / s_height
            );

            glm::vec2 tr;
            glm::vec2 tl;
            glm::vec2 br;
            glm::vec2 bl;

            tr = glm::vec2(localizedPosition.x + (localizedSize.x / 2.0), localizedPosition.y + (localizedSize.y / 2.0));
            tl = glm::vec2(localizedPosition.x - (localizedSize.x / 2.0), localizedPosition.y + (localizedSize.y / 2.0));
            br = glm::vec2(localizedPosition.x + (localizedSize.x / 2.0), localizedPosition.y - (localizedSize.y / 2.0));
            bl = glm::vec2(localizedPosition.x - (localizedSize.x / 2.0), localizedPosition.y - (localizedSize.y / 2.0));

            vertices = new float[12];
            float _v[] = {
                tr.x, tr.y,
                bl.x, bl.y,
                br.x, br.y,
                tr.x, tr.y,
                tl.x, tl.y,
                bl.x, bl.y
            }; 
            for (int i = 0; i < 12; i++) {
                vertices[i] = _v[i];
            }
            

            this->position = localizedPosition;
            this->size = localizedSize;
        }
    };
}