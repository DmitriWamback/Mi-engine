/* 
-- FRAMEBUFFER --
The framebuffer is used to determine how a scene should be rendered to a render texture
*/

namespace mi {

    enum BUFFER_TYPE {
        STANDARD = 0x008C,
        DEPTH    = 0x008D
    };

    
    class Framebuffer {
    public:
        uint32_t tex_id;
        uint32_t fbo;

        int WIDTH, HEIGHT;

        BUFFER_TYPE type;

        Framebuffer() {}

        Framebuffer(int WIDTH, int HEIGHT) {
            type = STANDARD;
        }
    };
    /* classes inheriting from the Framebuffer class*/

    class Depthbuffer: public Framebuffer {
    private:
    
    public:

        Depthbuffer(int WIDTH, int HEIGHT) {

            type = DEPTH;
            this->WIDTH = WIDTH;
            this->HEIGHT = HEIGHT;
            glGenFramebuffers(1, &fbo);
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
            glGenTextures(1, &tex_id);

            std::cout << this->WIDTH << std::endl;

            glBindTexture(GL_TEXTURE_2D, tex_id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->WIDTH, this->HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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