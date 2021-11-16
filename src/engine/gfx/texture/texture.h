/* 
-- TEXTURE --
The texture is an image that can be rendered on the surfaces of a polygon
Furthermore, the RenderTexture is used mainly for holding the texture of a rendered scene
*/

namespace mi {

    class Texture {
    public:
        int tex_id;

        Texture() {}

        Texture(const char* file_path) {

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