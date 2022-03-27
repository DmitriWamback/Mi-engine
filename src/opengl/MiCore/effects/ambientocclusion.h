namespace Mi { namespace PostProcessing {

    class AmbientOcclusion: public Mi::PostProcessing::Effect {
    public:

        Effect* Create(std::map<const char*, uint32_t> renders) {

            uint32_t albedo      = renders[MI_DEFERRED_RENDER_ALBEDO_KEY];
            uint32_t normal      = renders[MI_DEFERRED_RENDER_NORMAL_KEY];
            uint32_t position    = renders[MI_DEFERRED_RENDER_POSITION_KEY];
        }

        uint32_t Use(std::map<const char*, uint32_t> r) {
            
        }
    };
}}