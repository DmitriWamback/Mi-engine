#if !defined(MI_COMPONENT_IMPLEMENTATION)
#define MI_COMPONENT_IMPLEMENTATION

namespace Mi {
    class RAttribute {
    public:
        RenderBuffer buffer;        

        RAttribute() {}
        RAttribute(RenderBuffer buffer) {}

        // Updates the attribute with a shader
        virtual void Update(Mi::Shader& shader) {}

        // Updates the attribute
        virtual void Update() {}

        void __ATTRUPDATE(Mi::Shader& shader) {
            Update();
            Update(shader);
        }

        template<class T>
        T CastTo() {
            return dynamic_cast<T>(this);
        }
    };

    class RRenderer {
    public:

        RenderBuffer buffer;
        std::vector<Mi::Texture> textures;

        RRenderer() {}
        RRenderer(RenderBuffer buffer) {}

        // Updates the attribute with a shader
        virtual void Update(Mi::Shader& shader) {}

        // Updates the attribute
        virtual void Update() {}

        virtual float* GetVertices() { return nullptr; }
        virtual int GetVertexSize()  { return 0; }

        void __ATTRUPDATE(Mi::Shader& shader) {
            Update();
            Update(shader);
        }
    };
}

#endif