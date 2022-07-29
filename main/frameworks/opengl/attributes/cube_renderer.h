namespace Mi {

    class CubeRenderer {
    public:
        static std::vector<float> vertices;

        CubeRenderer() {
            
        }
    };

    std::vector<float> CubeRenderer::vertices = std::vector<float> {
        -1.0f, -1.0f, -1.0f, /* POSITIONS */  0.0f,  0.0f, -1.0f, /* NORMALS */ 0.0f, 0.0f /* UV COORDS */,
         1.0f,  1.0f, -1.0f,                  0.0f,  0.0f, -1.0f,               1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,                  0.0f,  0.0f, -1.0f,               1.0f, 0.0f,
         1.0f,  1.0f, -1.0f,                  0.0f,  0.0f, -1.0f,               1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,                  0.0f,  0.0f, -1.0f,               0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,                  0.0f,  0.0f, -1.0f,               0.0f, 1.0f,
        
        -1.0f, -1.0f,  1.0f,                  0.0f,  0.0f,  1.0f,               1.0f, 0.0f, 
         1.0f, -1.0f,  1.0f,                  0.0f,  0.0f,  1.0f,               0.0f, 0.0f, 
         1.0f,  1.0f,  1.0f,                  0.0f,  0.0f,  1.0f,               0.0f, 1.0f, 
         1.0f,  1.0f,  1.0f,                  0.0f,  0.0f,  1.0f,               0.0f, 1.0f, 
        -1.0f,  1.0f,  1.0f,                  0.0f,  0.0f,  1.0f,               1.0f, 1.0f, 
        -1.0f, -1.0f,  1.0f,                  0.0f,  0.0f,  1.0f,               1.0f, 0.0f, 
        
        -1.0f,  1.0f,  1.0f,                 -1.0f,  0.0f,  0.0f,               0.0f, 1.0f, 
        -1.0f,  1.0f, -1.0f,                 -1.0f,  0.0f,  0.0f,               1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,                 -1.0f,  0.0f,  0.0f,               1.0f, 0.0f, 
        -1.0f, -1.0f, -1.0f,                 -1.0f,  0.0f,  0.0f,               1.0f, 0.0f, 
        -1.0f, -1.0f,  1.0f,                 -1.0f,  0.0f,  0.0f,               0.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,                 -1.0f,  0.0f,  0.0f,               0.0f, 1.0f, 
        
         1.0f,  1.0f,  1.0f,                  1.0f,  0.0f,  0.0f,               0.0f, 1.0f, 
         1.0f, -1.0f, -1.0f,                  1.0f,  0.0f,  0.0f,               1.0f, 0.0f,
         1.0f,  1.0f, -1.0f,                  1.0f,  0.0f,  0.0f,               1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,                  1.0f,  0.0f,  0.0f,               1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,                  1.0f,  0.0f,  0.0f,               0.0f, 1.0f,
         1.0f, -1.0f,  1.0f,                  1.0f,  0.0f,  0.0f,               0.0f, 0.0f,
        
        -1.0f, -1.0f, -1.0f,                  0.0f, -1.0f,  0.0f,               0.0f, 1.0f,
         1.0f, -1.0f, -1.0f,                  0.0f, -1.0f,  0.0f,               1.0f, 1.0f,
         1.0f, -1.0f,  1.0f,                  0.0f, -1.0f,  0.0f,               1.0f, 0.0f,
         1.0f, -1.0f,  1.0f,                  0.0f, -1.0f,  0.0f,               1.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,                  0.0f, -1.0f,  0.0f,               0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,                  0.0f, -1.0f,  0.0f,               0.0f, 1.0f,
        
        -1.0f,  1.0f, -1.0f,                  0.0f,  1.0f,  0.0f,               0.0f, 1.0f,
         1.0f,  1.0f , 1.0f,                  0.0f,  1.0f,  0.0f,               1.0f, 0.0f,
         1.0f,  1.0f, -1.0f,                  0.0f,  1.0f,  0.0f,               1.0f, 1.0f,
         1.0f,  1.0f,  1.0f,                  0.0f,  1.0f,  0.0f,               1.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,                  0.0f,  1.0f,  0.0f,               0.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,                  0.0f,  1.0f,  0.0f,               0.0f, 0.0f
    };
}