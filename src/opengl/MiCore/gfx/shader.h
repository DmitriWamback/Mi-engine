/* 
-- SHADER --
The shader is used for loading special programs that determine the shape and color of an object
*/

std::string BASE_SHADER_PATH = "src/res/shaders/glsl/";

class Shader {
public:
    int program;
    std::string shaderName;

    Shader() {}

    Shader(const char* vertexShaderPath, const char* fragmentShaderPath, std::string name) {

        shaderName = name;

        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        shaderName = name;

        std::ifstream _vs, _fs;
        std::stringstream vss, fss;

        _vs.open(std::string("src/res/shaders/glsl/").append(vertexShaderPath));
        _fs.open(std::string("src/res/shaders/glsl/").append(fragmentShaderPath));
        vss << _vs.rdbuf();
        fss << _fs.rdbuf();

        std::string _vss = vss.str();
        std::string _fss = fss.str();

        const char* _vSRC = _vss.c_str();
        const char* _fSRC = _fss.c_str();

        int nbVertexShaderImports    = 0;
        int nbFragmentShaderImports  = 0;
        char** vertexShaderImports   = load_shader_imports(&nbVertexShaderImports, _vSRC);
        char** fragmentShaderImports = load_shader_imports(&nbFragmentShaderImports, _fSRC);

        std::string vFullSource = _vSRC;
        std::string fFullSource = _fSRC;
        
        for (int i = 0; i < nbVertexShaderImports; i++) {
            importExternalShader(&vFullSource, _vSRC, vertexShaderImports[i]);
        }   

        for (int i = 0; i < nbFragmentShaderImports; i++) {
            importExternalShader(&fFullSource, _fSRC, fragmentShaderImports[i]);
        }

        const char* vSRC = vFullSource.c_str();
        const char* fSRC = fFullSource.c_str();

        glShaderSource(vertexShader, 1, &vSRC, NULL);
        glShaderSource(fragmentShader, 1, &fSRC, NULL);
        glCompileShader(vertexShader);
        glCompileShader(fragmentShader);

        compileShader(vertexShader);
        compileShader(fragmentShader);

        program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
    }

    void importExternalShader(std::string* out, const char* src, char* path) {

        std::ifstream import;
        std::stringstream stream;

        std::string fsp = std::string("src/res/shaders/lib/").append(path);
        std::string fsc;
        import.open(fsp);
        stream << import.rdbuf();
        fsc = stream.str();
        out->append("\n\n").append(fsc);
    }

    void compileShader(int shader) {
        int success;
        char infoLog[1024];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILE_ERROR of type: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }

    void setMatr4(std::string name, glm::mat4 &matr) {
        int loc = glGetUniformLocation(program, name.c_str());
        glUniformMatrix4fv(loc, 1, GL_FALSE, &matr[0][0]);
    }

    void setVec3(std::string name, glm::vec3 vect) {
        int loc = glGetUniformLocation(program, name.c_str());
        glUniform3f(loc, vect.x, vect.y, vect.z);
    }

    void setInt(std::string name, int a) {
        int loc = glGetUniformLocation(program, name.c_str());
        glUniform1i(loc, a);
    }

    void setFloat(std::string name, float a) {
        int loc = glGetUniformLocation(program, name.c_str());
        glUniform1f(loc, a);
    }

    void use() {
        glUseProgram(program);
    }
};