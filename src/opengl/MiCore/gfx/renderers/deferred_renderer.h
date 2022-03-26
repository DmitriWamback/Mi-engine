#define MI_DEFERRED_RENDER_ALBEDO_KEY   "_albedo"
#define MI_DEFERRED_RENDER_NORMAL_KEY   "_normal"
#define MI_DEFERRED_RENDER_POSITION_KEY "_position"

namespace Mi { namespace Enum {

    enum RENDERABLERENDERTYPE {
        STANDARD,
        DEFERRED
    };
}}

namespace Mi {

    class DeferredRenderer: public Mi::Renderer {
    public:

        std::vector<Mi::Inheritable::Renderable> renderables;
        std::vector<Mi::PostProcessing::Effect*> effects;
        Mi::ColorBuffer c_buffer;
        Shader deferredShader;
        
        // Creates a default Deferred Renderer
        // IMPORTANT:
        // The color attachment 0 is used for the albedo property
        // The color attachment 1 is used for the normal property
        // The color attachment 2 is used for the position property
        static DeferredRenderer* Create() {
            Shader ds = Shader("deferred/vMain.glsl", "deferred/fMain.glsl", "DEFERRED STANDARD");
            DeferredRenderer* renderer = new DeferredRenderer();
            renderer->deferredShader = ds;

            Mi::ColorBuffer cbuf = Mi::ColorBuffer::Create();
            cbuf.AddColorAttachment(0, MI_DEFERRED_RENDER_ALBEDO_KEY);      // albedo        (index specified in the fragment shader) => layout (location = 0) out [...]
            cbuf.AddColorAttachment(1, MI_DEFERRED_RENDER_NORMAL_KEY);      // normal        (index specified in the fragment shader) => layout (location = 1) out [...]
            cbuf.AddColorAttachment(2, MI_DEFERRED_RENDER_POSITION_KEY);    // position      (index specified in the fragment shader) => layout (location = 2) out [...]

            renderer->c_buffer = cbuf;
            return renderer;
        }

        void AddEffect(Mi::PostProcessing::Effect* effect) {
            effects.push_back(effect);
        }

        std::map<const char*, uint32_t> Render(Mi::Camera camera) {

            c_buffer.Bind();
            deferredShader.use();
            deferredShader.setMatr4("projection", camera.projection);
            deferredShader.setMatr4("view", camera.view);
            for (int i = 0; i < renderables.size(); i++) {
                renderables[i].render(deferredShader);
            }
            c_buffer.Unbind();

            return c_buffer.GetResults();
        }
    };
}