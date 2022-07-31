namespace Mi { namespace Frame {
    
    class ColorBuffer {
    public:
        uint32_t fbo;
        static ColorBuffer Create(int size);

        void AddAttachment(std::string name, uint32_t location);
    private:
        std::map<std::string, uint32_t> textures;
    };

    ColorBuffer ColorBuffer::Create(int size) {
        ColorBuffer buffer = ColorBuffer();
        glGenFramebuffers(1, &buffer.fbo);

        return buffer;
    }

    void ColorBuffer::AddAttachment(std::string name, uint32_t location) {

    }
}}