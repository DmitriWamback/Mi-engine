/* 
-- FRAMEBUFFER --
The framebuffer is used to determine how a scene should be rendered to a render texture
*/

namespace mi_enum {

    enum BUFFERTYPE {
        BUFTYPE_STANDARD            = 0x008C,
        BUFTYPE_DEPTH               = 0x008D,
        BUFTYPE_POINTDEPTH          = 0x008E
    };

}

namespace mi_inheritable {
    
    class Framebuffer {
    public:
        uint32_t tex_id;
        uint32_t fbo;

        int WIDTH, HEIGHT;

        mi_enum::BUFFERTYPE type;

        Framebuffer() {}

        Framebuffer(int WIDTH, int HEIGHT) {
            type = mi_enum::BUFTYPE_STANDARD;
        }
    };
}

/* classes inheriting from the Framebuffer class*/

namespace mi {
    class Depthbuffer: public mi_inheritable::Framebuffer {
    private:

    public:

        Depthbuffer(int WIDTH, int HEIGHT) {

            type = mi_enum::BUFTYPE_DEPTH;
            this->WIDTH = WIDTH;
            this->HEIGHT = HEIGHT;
            glGenFramebuffers(1, &fbo);
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
            glGenTextures(1, &tex_id);

            glBindTexture(GL_TEXTURE_2D, tex_id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->WIDTH, this->HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            glDepthFunc(GL_LEQUAL);
            float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex_id, 0);
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
    };
}