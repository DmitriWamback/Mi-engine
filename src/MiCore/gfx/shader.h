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
        const char* vSRC = _vss.c_str();
        const char* fSRC = _fss.c_str();

        int nbVertexShaderImports    = 0;
        int nbFragmentShaderImports  = 0;
        char** vertexShaderImports   = load_shader_imports(&nbVertexShaderImports, vSRC);
        char** fragmentShaderImports = load_shader_imports(&nbFragmentShaderImports, fSRC);

        for (int i = 0; i < nbVertexShaderImports; i++) {
            std::cout << std::string("src/res/shaders/lib/").append(vertexShaderImports[i]) << std::endl;
        }

        for (int i = 0; i < nbFragmentShaderImports; i++) {
            std::cout << std::string("src/res/shaders/lib/").append(fragmentShaderImports[i]) << std::endl;
        }

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

    void compileShader(int shader) {
        int success;
        char infoLog[1024];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILE_ERROR of type: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }

    void setMatr4(std::string name, mi::Matr4 matr) {
        int loc = glGetUniformLocation(program, name.c_str());
        float dat[] = {
            matr.r1.x, matr.r1.y, matr.r1.z, matr.r1.w,
            matr.r2.x, matr.r2.y, matr.r2.z, matr.r2.w, 
            matr.r3.x, matr.r3.y, matr.r3.z, matr.r3.w, 
            matr.r4.x, matr.r4.y, matr.r4.z, matr.r4.w
        };
        glUniformMatrix4fv(loc, 1, GL_FALSE, dat);
    }

    void setVec3(std::string name, mi::Vec3 vect) {
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