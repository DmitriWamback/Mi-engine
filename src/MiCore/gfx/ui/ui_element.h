namespace mi_inheritable {

    class UIElement {
    public:
        mi::Vec2 position;
        float rotation;
        mi::Vec2 size;
        renderbuf buf;

        float* vertices;

        bool scaleWithScreenSize = false;

        UIElement() {}

        UIElement(renderbuf buffer, mi::Vec2 screenPositionPXL, mi::Vec2 screenSizePXL) {
            this->buf = buffer;
            Initialize(screenPositionPXL, screenSizePXL);
        }

        virtual void Render(Shader& shader) {

        }

        void Initialize(mi::Vec2 screenPositionPXL, mi::Vec2 screenSizePXL) {
            int s_width, s_height;
            glfwGetWindowSize(main_window, &s_width, &s_height);

            mi::Vec2 localizedPosition = mi::Vec2(
                screenPositionPXL.x / s_width,
                screenPositionPXL.y / s_height
            );

            mi::Vec2 localizedSize = mi::Vec2(
                screenSizePXL.x / s_width,
                screenSizePXL.y / s_height
            );

            mi::Vec2 tr;
            mi::Vec2 tl;
            mi::Vec2 br;
            mi::Vec2 bl;

            tr = mi::Vec2(localizedPosition.x + (localizedSize.x / 2.0), localizedPosition.y + (localizedSize.y / 2.0));
            tl = mi::Vec2(localizedPosition.x - (localizedSize.x / 2.0), localizedPosition.y + (localizedSize.y / 2.0));
            br = mi::Vec2(localizedPosition.x + (localizedSize.x / 2.0), localizedPosition.y - (localizedSize.y / 2.0));
            bl = mi::Vec2(localizedPosition.x - (localizedSize.x / 2.0), localizedPosition.y - (localizedSize.y / 2.0));

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