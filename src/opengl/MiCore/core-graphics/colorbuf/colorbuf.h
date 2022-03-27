namespace Mi {

    class ColorBuffer {
    public:

        std::map<const char*, uint32_t> color_buffers;
        std::vector<int> attachments;
        uint32_t fbo;
        uint32_t rbo;

        static ColorBuffer Create() {
            
            uint32_t _fbo;
            uint32_t _rbo;
            glGenFramebuffers(1, &_fbo);

            glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
            glGenRenderbuffers(1, &_rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 2000, 2000);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            ColorBuffer c_buffer = ColorBuffer();
            c_buffer.fbo = _fbo;
            return c_buffer;
        }

        void AddColorAttachment(int attribPosition, const char* key) {
            int attr = GL_COLOR_ATTACHMENT0 + attribPosition;

            glBindFramebuffer(GL_FRAMEBUFFER, fbo);

            uint32_t cbuf;
            glGenTextures(1, &cbuf);
            glBindTexture(GL_TEXTURE_2D, cbuf);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2000, 2000, 0, GL_RGBA, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glFramebufferTexture2D(GL_FRAMEBUFFER, attr, GL_TEXTURE_2D, cbuf, 0);
            
            color_buffers[key] = cbuf;
            attachments.push_back(attr);

            uint32_t _attachments[attachments.size()];
            for (int i = 0; i < attachments.size(); i++) {
                _attachments[i] = attachments[i];
            }
            glDrawBuffers(attachments.size(), _attachments);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void AddRBO() {

        }

        void Bind() {
            glViewport(0, 0, 2000, 2000);
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