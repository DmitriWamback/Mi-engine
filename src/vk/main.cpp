#include "mi-core/engine.h"

int main() {

    try {
        Mi::Engine::vMiEngineBegin(1200, 800);
        Mi::Engine::vMiEngineStartMainLoop();
    }
    catch(const std::exception& e) {}
}