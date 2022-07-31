namespace Mi { 

    class Shader {
    public:
        uint32_t program;
        std::map<std::string, int> locationCache;

        static Shader Create();

        void setFloat(std::string location, float value);
    };

    Shader Shader::Create() {

        return Shader();
    }
}