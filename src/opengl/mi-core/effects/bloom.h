namespace Mi { namespace PostProcessing {

    class Bloom: public Mi::PostProcessing::Effect {
    public:

        float threshold;
        float intensity;

        static Effect* Create(std::map<const char*, uint32_t> renders) {
            uint32_t albedo_tex = renders[MI_DEFERRED_RENDER_ALBEDO_KEY];
            uint32_t normal_tex = renders[MI_DEFERRED_RENDER_NORMAL_KEY];
            return new Effect();
        }

        
    };
}}