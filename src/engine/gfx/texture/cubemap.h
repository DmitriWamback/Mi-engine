namespace mi {

    class CubeMap {
    public:

        uint32_t tex_id;
        
        CubeMap() {}

        CubeMap(std::string image_paths[]) {

            glGenTextures(1, &tex_id);
            glBindTexture(GL_TEXTURE_CUBE_MAP, tex_id);

            unsigned char* dat;
            int width, height, channels;

            for (int i = 0; i < 6; i++) {
                dat = stbi_load(image_paths[i].c_str(), &width, &height, &channels, 0);
                if (channels == 3) {
                    glTexImage2D(
                        GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                        0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dat);
                }
                else if (channels == 4) {
                    glTexImage2D(
                        GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                        0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dat);
                }
            }

            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        }
    };
}