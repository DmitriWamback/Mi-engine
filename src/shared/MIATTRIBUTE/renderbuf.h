class RenderBuffer {
public:

    uint32_t VertexArrayObject;
    uint32_t VertexBufferObject;
    uint32_t IndexBufferObject;

    static RenderBuffer Create() {
        RenderBuffer r = RenderBuffer();

#if defined(MI_ENGINE_OPENGL)
        glGenVertexArrays(1, &r.VertexArrayObject);
        glGenBuffers(1, &r.VertexBufferObject);
        glGenBuffers(1, &r.IndexBufferObject);
#endif

        return r;
    }
};