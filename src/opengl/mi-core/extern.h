#define MI_VERTEX       0
#define MI_NORMAL       1
#define MI_UV           2

#define MI_I_VERTEX     0
#define MI_I_NORMAL     2
#define MI_I_UV         1


extern "C" {
    uint32_t* load_model_indices(const char* file_path, int* index_count, int type);
    const float* load_model_vertices(const char* file_path, int* vertex_count, int type);
    const char* GLSLImport(const char* shaderSource);
}