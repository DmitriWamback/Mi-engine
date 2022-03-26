#define MI_DEFERRED_RENDER_ALBEDO_KEY   "_albedo"
#define MI_DEFERRED_RENDER_NORMAL_KEY   "_normal"
#define MI_DEFERRED_RENDER_POSITION_KEY "_position"

namespace Mi {

    class DeferredRenderer: public Mi::Renderer {
    public:

        std::vector<Mi::Inheritable::Renderable> renderables;
        std::vector<Mi::PostProcessing::Effect*> effects;
        Shader deferredShader;

        static DeferredRenderer* Create() {
            Shader ds = Shader("deferred/vMain.glsl", "deferred/fMain.glsl", "DEFERRED STANDARD");
            DeferredRenderer* renderer = new DeferredRenderer();
            renderer->deferredShader = ds;
            return renderer;
        }

        void AddEffect(Mi::PostProcessing::Effect* effect) {
            effects.push_back(effect);
        }

        std::map<const char*, Mi::ColorBuffer> Render(Mi::Camera camera) {

        }
    };
}