namespace Mi {

    class CubeNoise: public Mi::Inheritable::Renderable {
    private:
        Mi::Inheritable::Renderable* cubes[10000];
        int nb_cubes;
        glm::vec2 size;

    public:

        float seed;

        CubeNoise(renderbuf buffer, glm::vec3 position, glm::vec2 size, float seed) {

            nb_cubes = 0;
            type = Mi::Enum::ENT_NOISE_CUBE;
            this->buf = buffer;
            this->position = position;

            float _density = 0.4;
            this->size = size;
            this->seed = seed;

            for (int x = 0; x < size.x; x++) {
                for (int y = 0; y < size.y; y++) {
                    for (int z = 0; z < size.x; z++) {
                        
                        float density = get_noise_density_at(x + position.x, y + position.y, z + position.z, seed, 17.3);
                        float up    = get_noise_density_at(x + position.x,   y+1 + position.y, z + position.z, seed, 17.3);
                        float down  = get_noise_density_at(x + position.x,   y-1 + position.y, z + position.z, seed, 17.3);
                        float left  = get_noise_density_at(x-1 + position.x, y + position.y,   z + position.z, seed, 17.3);
                        float right = get_noise_density_at(x+1 + position.x, y + position.y,   z + position.z, seed, 17.3);
                        float front = get_noise_density_at(x + position.x,   y + position.y, z-1 + position.z, seed, 17.3);
                        float back  = get_noise_density_at(x + position.x,   y + position.y, z+1 + position.z, seed, 17.3);

                        bool has_empty_space = false;
                        if (up <= _density || down <= _density || left <= _density || right <= _density || front <= _density || back <= _density) has_empty_space = true;

                        if (density > _density && has_empty_space) {
                            glm::vec3 _position = glm::vec3((x - size.x/2), (y - size.y/2), (z - size.x/2)) + position;

                            Mi::Inheritable::Renderable* en = new Cube(buffer);
                            en->position = _position;
                            en->size = glm::vec3(1.0);
                            cubes[nb_cubes] = en;
                            nb_cubes++;
                        }
                    }
                }
            }
        }

        void push_to(glm::vec3 pos, float seed) {
            float _density = 0.4;

            for (int i = 0; i < nb_cubes; i++) {
                cubes[i] = nullptr;
            }

            nb_cubes = 0;

            for (int x = 0; x < size.x; x++) {
                for (int y = 0; y < size.y; y++) {
                    for (int z = 0; z < size.x; z++) {
                        
                        float density = get_noise_density_at(x + pos.x, y + pos.y, z + pos.z, seed, 17.3);
                        float up    = get_noise_density_at(x + pos.x,   y+1 + pos.y, z + pos.z, seed, 17.3);
                        float down  = get_noise_density_at(x + pos.x,   y-1 + pos.y, z + pos.z, seed, 17.3);
                        float left  = get_noise_density_at(x-1 + pos.x, y + pos.y,   z + pos.z, seed, 17.3);
                        float right = get_noise_density_at(x+1 + pos.x, y + pos.y,   z + pos.z, seed, 17.3);
                        float front = get_noise_density_at(x + pos.x,   y + pos.y, z-1 + pos.z, seed, 17.3);
                        float back  = get_noise_density_at(x + pos.x,   y + pos.y, z+1 + pos.z, seed, 17.3);

                        bool has_empty_space = false;
                        if (up <= _density || down <= _density || left <= _density || right <= _density || front <= _density || back <= _density) has_empty_space = true;

                        if (density > _density && has_empty_space) {
                            glm::vec3 _position = glm::vec3((x - size.x/2), (y - size.y/2), (z - size.x/2)) + pos;

                            Mi::Inheritable::Renderable* en = new Cube(buf);
                            en->position = _position;
                            en->size = glm::vec3(1.0);
                            cubes[nb_cubes] = en;
                            nb_cubes++;
                        }
                    }
                }
            }
        }

        void render(Shader& shader) {
            if (shouldRender) {
                for (int i = 0; i < nb_cubes; i++) {
                    Mi::Inheritable::Renderable* e = cubes[i];
                    cubes[i]->render(shader);
                }
            }
        }
        
        void renderWithWireFrame(Shader& shader, Shader& wireframeShader) {
            if (shouldRender) {
                for (int i = 0; i < nb_cubes; i++) {
                    Mi::Inheritable::Renderable* e = cubes[i];
                    cubes[i]->renderWithWireFrame(shader, wireframeShader);
                }
            }
        }
    };
}