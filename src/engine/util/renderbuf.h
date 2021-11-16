class renderbuf {
public:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ibo;

    renderbuf() {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ibo);
    }
};