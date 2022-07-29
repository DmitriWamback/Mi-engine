#ifdef MI_APPLE_IMPLEMENTATION
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    #include <OpenAL/OpenAL.h>
#else
    #include <AL/al.h>
#endif
#include "sndfile.h"
#include "audiosource.h"

namespace Mi { namespace Audio {

    class AudioPlayer {
    private:
        std::vector<AudioSource> sources;

    public:

        void AddSource(AudioSource source) {
            sources.push_back(source);
        }
    };
}}