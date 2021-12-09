extern "C" {
    uint32_t* load_model_vertex_indices(const char* file_path, int* index_count);
    const float* load_model_vertices(const char* file_path, int* vertex_count);
    char** load_shader_imports(int* length, const char* shaderSource);
}