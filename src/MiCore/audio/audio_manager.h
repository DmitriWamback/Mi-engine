#ifdef __APPLE__
    #include <OpenAL/OpenAL.h>
#else
    #include <AL/al.h>
#endif

#include "sndfile.h"
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

namespace mi_audio {

    struct ADOPROP {
        float pitch;
        float volume;
        uint32_t buf;
        mi::Vec3 position;
        mi::Vec3 velocity;
        bool looped;
    };

    class AudioSource {
    private:
        ALuint source;
        struct ADOPROP props;

        void set_properties(struct ADOPROP properties) {

            position = properties.position;
            velocity = properties.velocity;

            alSourcef(source, AL_PITCH,     properties.pitch);
            alSourcef(source, AL_GAIN,      properties.volume);
            alSourcef(source, AL_BUFFER,    properties.buf);
            alSourcei(source, AL_LOOPING,   properties.looped);

            alSource3f(source, AL_POSITION, properties.position.x, properties.position.y, properties.position.z);
            alSource3f(source, AL_VELOCITY, properties.velocity.x, properties.velocity.y, properties.velocity.z);
        }

        uint32_t LoadSound(const char* filepath) {
            ALenum ERR, FORMAT = AL_NONE;
            ALuint BUFFER;
            SNDFILE* sndfile;
            SF_INFO sf_info;
            short *membuf;
            sf_count_t num_frames;
            ALsizei num_bytes;

            sndfile = sf_open(filepath, SFM_READ, &sf_info);
            if (!sndfile) {
                std::cout << "failed to open file\n";
                return -1;
            }
            if (sf_info.frames < 1 || sf_info.frames > (sf_count_t)(INT_MAX / sizeof(short)) / sf_info.channels) {
                return -1;
            }

            if (sf_info.channels == 1) FORMAT = AL_FORMAT_MONO16;
            if (sf_info.channels == 2) FORMAT = AL_FORMAT_STEREO16;
            if (!FORMAT) {
                return -1;
            }
        
            membuf = static_cast<short*>(malloc((size_t)(sf_info.frames * sf_info.channels) * sizeof(short)));
            num_frames = sf_read_short(sndfile, membuf, sf_info.frames);
            if(num_frames < 1) {
                free(membuf);
                sf_close(sndfile);
                fprintf(stderr, "Failed to read samples in %s (%" PRId64 ")\n", filepath, num_frames);
                return -1;
            }
            num_bytes = (ALsizei)(num_frames * sf_info.channels) * (ALsizei)sizeof(short);

            alGenBuffers(1, &BUFFER);
            alBufferData(BUFFER, FORMAT, membuf, num_bytes, sf_info.samplerate);
            free(membuf);
            sf_close(sndfile);

            ERR = alGetError();
            if(ERR != AL_NO_ERROR) {
                if(BUFFER && alIsBuffer(BUFFER)) alDeleteBuffers(1, &BUFFER);
                return 0;
            }
            return BUFFER;
        }

    public:
        std::string name;
        bool staticSound;
        mi::Vec3 position;
        mi::Vec3 velocity;

        ALuint GetSource() {
            return source;
        }
        uint32_t GetBuffer() {
            return props.buf;
        }

        AudioSource() {}

        AudioSource(struct ADOPROP properties, const char* filepath, std::string name) {
            this->name = name;
            props = properties;
            alGenSources(1, &source);
            props.buf = LoadSound(filepath);
            set_properties(props);
        }
    };

    class AudioPlayer {
    private:
        ALCdevice* device;
        ALCcontext* context;

    public:

        AudioPlayer() {
            device = alcOpenDevice(nullptr);
            context = alcCreateContext(device, nullptr);
            alcMakeContextCurrent(context);

            /*
            const ALchar* device_name;
            if (alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT"))
                device_name = alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
            
            if (!device_name || alcGetError(device) != AL_NO_ERROR)
                device_name = alcGetString(device, ALC_DEVICE_SPECIFIER);
            */
        }

        void PlaySound(AudioSource source) {
            alSourcei(source.GetSource(), AL_BUFFER, source.GetBuffer());
            alSourcePlay(source.GetSource());
        }

        void StopSound(AudioSource source) {
            alSourcei(source.GetSource(), AL_BUFFER, source.GetBuffer());
            alSourceStop(source.GetSource());
        }
    };
}