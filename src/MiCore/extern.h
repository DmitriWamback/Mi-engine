extern "C" {
    const float* load_model_vertices(const char* file_path);
    char** load_shader_imports(int* length, const char* shaderSource);
}