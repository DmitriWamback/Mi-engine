#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
/* 
-- TEXTURE --
The texture is an image that can be rendered on the surfaces of a polygon
Furthermore, the RenderTexture is used mainly for holding the texture of a rendered scene
*/

namespace Mi {

    class Texture {
    public:
        uint32_t tex_id;

        Texture() {}

        static Texture Create(const char* file_path) {
            int width, height, channels;

            uint32_t tex;
            Texture t = Texture();

            unsigned char* data = stbi_load(file_path, &width, &height, &channels, 0);
            if (data) {
                glGenTextures(1, &tex);
                glBindTexture(GL_TEXTURE_2D, tex);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

                if (channels == 3) {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    glGenerateMipmap(GL_TEXTURE_2D);
                }
                if (channels == 4) {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                    glGenerateMipmap(GL_TEXTURE_2D);
                }
                stbi_image_free(data);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
            else {
                std::cout << "COULDN'T FIND IMAGE\n";
            }

            t.tex_id = tex;
            return t;
        };

        void Bind(int index) {
            glActiveTexture(GL_TEXTURE0 + index);
            glBindTexture(GL_TEXTURE_2D, tex_id);
        }

        static void Unbind(int index) {
            glActiveTexture(GL_TEXTURE0 + index);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        static void AttemptBind(uint32_t bindingId, int index) {
            glActiveTexture(GL_TEXTURE0 + index);
            glBindTexture(GL_TEXTURE_2D, bindingId);
        } 
    };

    class RenderTexture {
    public:
        int tex_id;

        RenderTexture() {}

        RenderTexture(int tex_id) {
            this->tex_id = tex_id;
        }

        void Bind(int index) {
            glActiveTexture(GL_TEXTURE0 + index);
            glBindTexture(GL_TEXTURE_2D, tex_id);
        }
    };  
}