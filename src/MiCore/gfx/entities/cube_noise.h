namespace mi {

    class CubeNoise: public mi_inheritable::Entity {
    private:
        mi_inheritable::Entity* cubes;
        int nb_cubes;

    public:

        CubeNoise(renderbuf buffer, mi::Vec3 position, int size) {
            this->buf = buffer;

            nb_cubes = 0;
            cubes = new mi_inheritable::Entity[size*size*size];
        }
    };
}