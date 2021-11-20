#define MAX_VERTICES 100000

/* 
-- ENTITY --
The entity is a base class for rendering hard-coded vertex placements
*/

class Entity {
private:
    mi::Matr4 model_matrix;

public:
    std::string shaderToUse;

    mi::Vec3 position;
    mi::Vec3 rotation;
    mi::Vec3 size;
    
    renderbuf buf;

    Entity() {
        position = mi::Vec3();
        rotation = mi::Vec3();
        size = mi::Vec3(1.0);
    }

    void create_model_matrix() {
        model_matrix = rotate(rotation) * scale(size / 2.0) * translate(position);
    }

    mi::Matr4 get_model() {
        return model_matrix;
    }

    virtual void render(Shader &shader) {
        shader.use();
        model_matrix = scale(mi::Vec3(1.0));

        shader.setMatr4("model", model_matrix);
    }
};