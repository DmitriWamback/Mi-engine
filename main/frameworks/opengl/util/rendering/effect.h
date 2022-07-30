namespace Mi {

    class Effect {
    public:
        virtual void Compute(std::map<std::string, uint32_t> textures) {}
    };
}