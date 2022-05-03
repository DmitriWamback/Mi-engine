/* 
-- SHADER --
The shader is used for loading special programs that determine the shape and color of an object
*/
#define MI_OPENGL_SHADER_IMPLEMENTATION

std::string BASE_SHADER_PATH = "src/res/shaders/glsl/";

namespace Mi { 
    class Shader {
    public:
        int program;
        std::string shaderName;

        Shader() {}

        static Shader Create(const char* vertexShaderPath, const char* fragmentShaderPath, std::string name) {
            

            Shader shader = Shader();
            shader.shaderName = name;

            int vertexShader = glCreateShader(GL_VERTEX_SHADER);
            int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

            std::ifstream _vs, _fs;
            std::stringstream vss, fss;

            _vs.open(std::string("src/res/shaders/glsl/sources/").append(vertexShaderPath));
            _fs.open(std::string("src/res/shaders/glsl/sources/").append(fragmentShaderPath));
            vss << _vs.rdbuf();
            fss << _fs.rdbuf();

            std::string _vss = vss.str();
            std::string _fss = fss.str();

            const char* _vSRC = _vss.c_str();
            const char* _fSRC = _fss.c_str();
            const char* vertexShaderImports   = GLSLImport(_vSRC);
            const char* fragmentShaderImports = GLSLImport(_fSRC);

            glShaderSource(vertexShader, 1, &vertexShaderImports, NULL);
            glShaderSource(fragmentShader, 1, &fragmentShaderImports, NULL);
            glCompileShader(vertexShader);
            glCompileShader(fragmentShader);

            compileShader(vertexShader);
            compileShader(fragmentShader);

            shader.program = glCreateProgram();
            glAttachShader(shader.program, vertexShader);
            glAttachShader(shader.program, fragmentShader);
            glLinkProgram(shader.program);

            return shader;
        }

        static void importExternalShader(std::string* out, const char* src, char* path) {

            std::ifstream import;
            std::stringstream stream;

            std::string fsp = std::string("src/res/shaders/lib/").append(path);
            std::string fsc;
            import.open(fsp);
            stream << import.rdbuf();
            fsc = stream.str();
            out->append("\n\n").append(fsc);
        }

        static void compileShader(int shader) {
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

        void setMultipleMatr4(std::map<std::string, glm::mat4&> mat) {
            for (std::map<std::string, glm::mat4&>::iterator t = mat.begin(); t != mat.end(); t++) setMatr4(t->first, t->second);
        }
        void setMultipleVec3(std::map<std::string, glm::vec3> vec) {
            for (std::map<std::string, glm::vec3>::iterator t = vec.begin(); t != vec.end(); t++) setVec3(t->first, t->second);
        }
        void setMultipleInt(std::map<std::string, int> i) {
            for (std::map<std::string, int>::iterator t = i.begin(); t != i.end(); t++) setInt(t->first, t->second);
        }
        void setMultipleFloat(std::map<std::string, float> f) {
            for (std::map<std::string, float>::iterator t = f.begin(); t != f.end(); t++) setFloat(t->first, t->second);
        }

        void use() {
            glUseProgram(program);
        }
    };
}