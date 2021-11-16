/* 
-- RENDERBUF --
The renderbuf is a way of keeping and limiting the use of VAOs, VBOs and IBOs (EBOs)
*/


class renderbuf {
public:
    uint32_t vao;
    uint32_t vbo;
    uint32_t ibo;

    renderbuf() {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ibo);
    }
};