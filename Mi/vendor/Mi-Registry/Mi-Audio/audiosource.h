namespace Mi { namespace Audio {

    class AudioSource {
    private:
        uint32_t source;
        uint32_t buffer;

    public:

        float volume;
        float pitch;
        bool looped;
        std::string name;

        AudioSource() {}
        static AudioSource Create(const char* audiofile, std::string name) {
            
            AudioSource s = AudioSource();
            s.name = name;
            s.volume = 1;
            s.pitch = 1;
            s.looped = false;
            alGenSources(1, &s.source);
            return s;
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
}}