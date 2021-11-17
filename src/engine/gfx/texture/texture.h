#include "stb_image.h"

/* 
-- TEXTURE --
The texture is an image that can be rendered on the surfaces of a polygon
Furthermore, the RenderTexture is used mainly for holding the texture of a rendered scene
*/

namespace mi {

    class Texture {
    public:
        uint32_t tex_id;

        Texture() {}

        Texture(const char* file_path) {
            int width, height, channels;
            unsigned char* data = stbi_load(file_path, &width, &height, &channels, 0);

            glGenTextures(1, &tex_id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            stbi_image_free(data);
        };

        void bind() {
            glBindTexture(GL_TEXTURE_2D, tex_id);
        }
    };

    class RenderTexture {
    public:
        int tex_id;

        RenderTexture() {}

        RenderTexture(int tex_id) {
            this->tex_id = tex_id;
        }

        void bind() {
            glBindTexture(GL_TEXTURE_2D, tex_id);
        }
    };  
}