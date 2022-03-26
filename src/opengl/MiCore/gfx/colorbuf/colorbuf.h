namespace Mi {

    class ColorBuffer {
    public:

        std::map<const char*, uint32_t> color_buffers;
        std::vector<int> attachments;
        uint32_t fbo;

        static ColorBuffer Create() {
            
            uint32_t _fbo;

            glGenFramebuffers(1, &_fbo);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            ColorBuffer c_buffer = ColorBuffer();
            c_buffer.fbo = _fbo;
            return c_buffer;
        }

        void AddColorAttachment(uint32_t attribPosition, const char* key) {
            uint32_t attr = GL_COLOR_ATTACHMENT0 + attribPosition;

            glBindFramebuffer(GL_FRAMEBUFFER, fbo);

            uint32_t cbuf;
            glGenTextures(GL_TEXTURE_2D, &cbuf);
            glBindTexture(GL_TEXTURE_2D, cbuf);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 1000, 1000, 0, GL_RGBA, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glFramebufferTexture2D(GL_FRAMEBUFFER, attr, GL_TEXTURE_2D, cbuf, 0);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glBindTexture(GL_TEXTURE_2D, 0);
            
            color_buffers[key] = cbuf;
            attachments.push_back(attr);

            uint32_t _attachments[attachments.size()];
            for (int i = 0; i < attachments.size(); i++) {
                _attachments[i] = attachments[i];
            }
            glDrawBuffers(attachments.size(), _attachments);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void Bind() {
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        }

        std::map<const char*, uint32_t> GetResults() {
            return color_buffers;
        }

        void Unbind() {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
    };
}