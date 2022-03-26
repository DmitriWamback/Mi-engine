namespace Mi { namespace PostProcessing {

    class Bloom: public Mi::PostProcessing::Effect {
    public:

        static Bloom* Create(std::map<const char*, Mi::ColorBuffer> renders) {
            Mi::ColorBuffer albedo = renders[MI_DEFERRED_RENDER_ALBEDO_KEY];
            Mi::ColorBuffer normal = renders[MI_DEFERRED_RENDER_NORMAL_KEY];

        }
    };
}}