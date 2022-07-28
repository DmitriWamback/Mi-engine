#include <ft2build.h>
#include FT_FREETYPE_H

namespace Mi { namespace IO {

    typedef struct {
        uint32_t texid;
        glm::ivec2 size;
        glm::ivec2 bearing;
        uint32_t advance;
    } Character;

    class Font {
    public:
        FT_Library ft;
        std::map<char, Character> characters;

        static Font* Create(const char* path) {

            Font* f = new Font();
            FT_Error errInit = FT_Init_FreeType(&f->ft);
            if (errInit) {
                std::cout << std::string(MI_FREE_TYPE_ERROR_CODE).append("Failed to initialize font\n");
                return nullptr;
            }
            FT_Face face;
            if (FT_New_Face(f->ft, path, 0, &face)) {
                std::cout << std::string(MI_FREE_TYPE_ERROR_CODE).append("Cannot open font \"").append(path) << "\"\n";
                return nullptr;
            }
            FT_Set_Pixel_Sizes(face, 0, 48);
#if defined(MI_ENGINE_OPENGL)
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
#endif

            for (unsigned char c = 0; c < 128; c++) {
                
                if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                    std::cout << std::string(MI_FREE_TYPE_ERROR_CODE).append("Failed to read glyph\n");
                    continue;
                }

                uint32_t tex;
#if defined(MI_ENGINE_OPENGL)
                glGenTextures(1, &tex);
                glBindTexture(GL_TEXTURE_2D, tex);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif

               Character character = {
                   tex,
                   glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                   glm::ivec2(face->glyph->bitmap_left,  face->glyph->bitmap_top),
                   static_cast<uint32_t>(face->glyph->advance.x)
               };
               f->characters.insert(std::pair<char, Character>(c, character));
            }

            FT_Done_Face(face);
            FT_Done_FreeType(f->ft);

            return f;
        }
    };
}}