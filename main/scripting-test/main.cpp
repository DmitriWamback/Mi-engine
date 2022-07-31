#include <LuaCpp.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

std::string readFile() {
    std::ifstream scriptSource;
    scriptSource.open("main/scripting-test/script.lua");

    std::stringstream s;
    s << scriptSource.rdbuf();
    scriptSource.close();

    return s.str();
}

LuaCpp::LuaContext lua;

std::string compile_and_run(std::string source) {
    try {
        lua.CompileStringAndRun(source);
        return "success";
    }
    catch(std::exception& e) {
        return e.what();
    }
}

int main() {

    std::string source = readFile();
    std::cout << compile_and_run(source) << '\n';
}