namespace mi {

    class Skybox: public mi_inheritable::Entity {
    public:

        mi::CubeMap cubemap;

        Skybox() {}
        
        Skybox(renderbuf buffer) {
            this->buf = buffer;
        }

        
    };
}