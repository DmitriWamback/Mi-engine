namespace Mi { namespace PostProcessing {

    class AmbientOcclusion: public Mi::PostProcessing::Effect {
    public:

        AmbientOcclusion* Create(std::map<const char*, Mi::ColorBuffer> renders) {

            Mi::ColorBuffer albedo      = renders[MI_DEFERRED_RENDER_ALBEDO_KEY];
            Mi::ColorBuffer normal      = renders[MI_DEFERRED_RENDER_NORMAL_KEY];
            Mi::ColorBuffer position    = renders[MI_DEFERRED_RENDER_POSITION_KEY];
        }
    };
}}