#define MI_DEFERRED_RENDER_ALBEDO_KEY       "_albedo"
#define MI_DEFERRED_RENDER_NORMAL_KEY       "_normal"
#define MI_DEFERRED_RENDER_POSITION_KEY     "_position"
#define MI_DEFERRED_RENDER_DEPTH_KEY        "_depth"
#define MI_DEFERRED_RENDER_METALLIC_KEY     "_metallic"
#define MI_DEFERRED_RENDER_ROUGHNESS_KEY    "_roughness"

namespace Mi { namespace Enum {

    enum RENDERABLERENDERTYPE {
        STANDARD,
        DEFERRED
    };
}}

namespace Mi {

    class DeferredRenderer: public Mi::Renderer {
    public:

        std::vector<Mi::Renderable> renderables;
        std::vector<Mi::PostProcessing::Effect*> effects;
        Mi::ColorBuffer c_buffer;
        Mi::Shader deferredShader;
        
        // Creates a default Deferred Renderer
        // IMPORTANT:
        // • The color attachment 0 is used for the albedo property
        // • The color attachment 1 is used for the normal property
        // • The color attachment 2 is used for the position property
        // • The color attachment 3 is used for the depth property
        static DeferredRenderer* Create() {
            Mi::Shader ds = Mi::Shader::Create("deferred/vMain.glsl", "deferred/fMain.glsl", "DEFERRED STANDARD");
            DeferredRenderer* renderer = new DeferredRenderer();
            renderer->deferredShader = ds;

            Mi::ColorBuffer cbuf = Mi::ColorBuffer::Create();
            cbuf.AddColorAttachment(0, MI_DEFERRED_RENDER_ALBEDO_KEY);      // albedo        (index specified in the fragment shader) => layout (location = 0) out [...]
            cbuf.AddColorAttachment(1, MI_DEFERRED_RENDER_NORMAL_KEY);      // normal        (index specified in the fragment shader) => layout (location = 1) out [...]
            cbuf.AddColorAttachment(2, MI_DEFERRED_RENDER_POSITION_KEY);    // position      (index specified in the fragment shader) => layout (location = 2) out [...]
            cbuf.AddColorAttachment(3, MI_DEFERRED_RENDER_DEPTH_KEY);
            cbuf.AddColorAttachment(4, MI_DEFERRED_RENDER_METALLIC_KEY);
            cbuf.AddColorAttachment(5, MI_DEFERRED_RENDER_ROUGHNESS_KEY);

            renderer->c_buffer = cbuf;
            return renderer;
        }

        void AddEffect(Mi::PostProcessing::Effect* effect) {
            effects.push_back(effect);
        }

        void AddRenderable(Mi::Renderable r) {
            renderables.push_back(r);
        }       

        std::map<const char*, uint32_t> GetBuffers(Mi::Camera camera) {
            
            c_buffer.Bind();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            deferredShader.use();
            deferredShader.setMatr4("projection", camera.projection);
            deferredShader.setMatr4("view", camera.view);
            deferredShader.setFloat("farplane", camera.farplane);
            deferredShader.setVec3("camera_position", camera.position);

            for (int i = 0; i < renderables.size(); i++) {
                renderables[i].render(deferredShader);
            }
            c_buffer.Unbind();

            return c_buffer.GetResults();
        }

        void Render(Mi::Camera camera) {

            std::map<const char*, uint32_t> buffers = GetBuffers(camera);
            uint32_t albedo = buffers[MI_DEFERRED_RENDER_ALBEDO_KEY];

            std::vector<uint32_t> postprocessing_effects;

            // Computing the postprocessing effects and storing their textures
            //if (effects.size() > 0) for (int i = 0; i < effects.size(); i++) postprocessing_effects.push_back(effects[i]->Compute(buffers));
        }
    };
}