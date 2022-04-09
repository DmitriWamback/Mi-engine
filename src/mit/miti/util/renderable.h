#include <cmath>

namespace MITI { namespace CoreGraphics {

    class renderbuf {
    public:

        uint32_t vertexBufferObject;
        uint32_t vertexArrayObject;
        uint32_t elementBufferObject;

        renderbuf() {
            glGenVertexArrays(1, &vertexArrayObject);
            glGenBuffers(1, &vertexBufferObject);
            glGenBuffers(1, &elementBufferObject);
        }
    };

    class Renderable {
    public:
        renderbuf buf;
        Renderable() {}
        static Renderable* Create(renderbuf buf);
        virtual void Render() {}
        float* GetVertices();
        float* GetVertexSize();
    };

    class Triangle: public Renderable {
    public:
        static Renderable* Create(renderbuf buf) {
            Renderable* t = new Triangle();
            t->buf = buf;

            int i = 0;
            for (int x = -size/2; x < size/2; x++) {
                for (int y = -size/2; y < size/2; y++) {
                    for (int z = -size/2; z < size/2; z++) {

                        float xc = (float)x/(float)size;
                        float yc = (float)y/(float)size;
                        float zc = (float)z/(float)size;
                        float intensity = (Mi::noise(xc * 14.f, yc * 14.f, zc * 14.f) + 1.f) / 2.f;

                        vertices[i] = x;
                        vertices[i+1] = y;
                        vertices[i+2] = z;
                        vertices[i+3] = intensity;
                        i+=4;
                    }
                }
            }

            glBindVertexArray(t->buf.vertexArrayObject);
            glBindBuffer(GL_ARRAY_BUFFER, t->buf.vertexBufferObject);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), NULL);
            glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glBindVertexArray(0);

            return t;
        }

        void Render() override {
            glBindVertexArray(buf.vertexArrayObject);
            glDrawArrays(GL_POINTS, 0, size * size * size * 3);
            glBindVertexArray(0);
        }
    private:
        static const int size = 100;
        static float vertices[size * size * size * 4];
    };
}}


float MITI::CoreGraphics::Triangle::vertices[] = {
    -0.5f, -0.5f, 0.0f, 0.1f,
     0.5f, -0.5f, 0.0f, 0.9f,
     0.0f,  0.5f, 0.0f, 0.9f,
};
