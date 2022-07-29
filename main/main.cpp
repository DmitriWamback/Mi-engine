#include "frameworks/opengl/engine.h"

void callback() {}

int main(int argc, char** argv) {
    
    Mi::Core::CreateContext(1200, 1200);
    Mi::Core::RunContext(callback);
}