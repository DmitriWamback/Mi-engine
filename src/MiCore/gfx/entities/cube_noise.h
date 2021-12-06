namespace mi {

    class CubeNoise: public mi_inheritable::Entity {
    private:
        mi_inheritable::Entity* cubes[10000];
        int nb_cubes;
        int size;

    public:

        float seed;

        CubeNoise(renderbuf buffer, mi::Vec3 position, int size, float seed) {

            nb_cubes = 0;
            type = mi_enum::ENT_NOISE_CUBE;
            this->buf = buffer;
            this->position = position;

            float _density = 0.4;
            this->size = size;
            this->seed = seed;

            for (int x = 0; x < size; x++) {
                for (int y = 0; y < size; y++) {
                    for (int z = 0; z < size; z++) {
                        
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
                            mi::Vec3 _position = mi::Vec3((x - size/2), (y - size/2), (z - size/2)) + position;

                            mi_inheritable::Entity* en = new Cube(buffer);
                            en->position = _position;
                            en->size = mi::Vec3(1.0);
                            cubes[nb_cubes] = en;
                            nb_cubes++;
                        }
                    }
                }
            }
        }

        void push_to(mi::Vec3 pos, float seed) {
            float _density = 0.4;

            for (int i = 0; i < nb_cubes; i++) {
                cubes[i] = nullptr;
            }

            nb_cubes = 0;

            for (int x = 0; x < size; x++) {
                for (int y = 0; y < size; y++) {
                    for (int z = 0; z < size; z++) {
                        
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
                            mi::Vec3 _position = mi::Vec3((x - size/2), (y - size/2), (z - size/2)) + pos;

                            mi_inheritable::Entity* en = new Cube(buf);
                            en->position = _position;
                            en->size = mi::Vec3(1.0);
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
                    mi_inheritable::Entity* e = cubes[i];
                    cubes[i]->render(shader);
                }
            }
        }
    };
}