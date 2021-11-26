namespace mi {

    class Skybox: public mi_inheritable::Entity {
    public:

        mi::CubeMap cubemap;

        Skybox() {}
        
        Skybox(renderbuf buffer, std::string images[]) {
            this->buf = buffer;
            cubemap = mi::CubeMap(images);
        }
    };
}