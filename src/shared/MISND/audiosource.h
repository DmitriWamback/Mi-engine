namespace mi_audio {

    class AudioSource {
    private:
        uint32_t source;
        uint32_t buffer;

    public:

        float volume    = 1;
        float pitch     = 1;
        bool looped     = false;
        std::string name;

        AudioSource() {}
        AudioSource(const char* audiofile, std::string name) {
            
            this->name = name;
            alGenSources(1, &source);
        }

        static AudioSource Load(const char* audiofile, std::string name) {

            AudioSource source = AudioSource(audiofile, name);
            source.LinkProperties();
            return source;
        }

        uint32_t GetSource() {
            return source;
        }

        uint32_t GetBuffer() {
            return buffer;
        }

        void LinkProperties() {

        }
    };
}