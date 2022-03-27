namespace Mi { namespace PostProcessing {
    
    class Effect {
    public:

#if defined(MI_ENGINE_OPENGL) && defined(MI_OPENGL_SHADER_IMPLEMENTATION)
        std::map<const char*, Shader> GL_shaders;
#elif defined(MI_ENGINE_VULKAN) && defined(MI_VULKAN_SHADER_IMPLEMENTATION)
        std::map<const char*, Shader> VK_shaders;
#endif

        uint32_t tex_result;
        float canvas[24];
        const char* shader_key;

        static Effect* Create(std::map<const char*, uint32_t> renders);

        uint32_t Compute(std::map<const char*, uint32_t> renders);
    };
}}