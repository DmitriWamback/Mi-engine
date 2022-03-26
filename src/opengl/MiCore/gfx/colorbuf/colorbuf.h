namespace Mi {

    class ColorBuffer {
    public:

        uint32_t color_buf;
        uint32_t fbo;

        static ColorBuffer Create(const char* key, int attribPosition) {
            int position = GL_COLOR_ATTACHMENT0 + attribPosition;
            
            uint32_t _color_buf;
            uint32_t _fbo;

            glGenFramebuffers(1, &_fbo);
            glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

            glGenTextures(1, &_color_buf);
            glBindTexture(GL_TEXTURE_2D, _color_buf);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 1000, 1000, 0, GL_RGBA, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glFramebufferTexture2D(GL_FRAMEBUFFER, position, GL_TEXTURE_2D, _color_buf, 0);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            ColorBuffer c_buffer = ColorBuffer();
            c_buffer.fbo = _fbo;
            c_buffer.color_buf = _color_buf;
            return c_buffer;
        }

        void Bind() {

        }
    };
}