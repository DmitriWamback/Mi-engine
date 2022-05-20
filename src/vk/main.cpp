#include "mi-core/engine.h"

int main() {

    try {
        Mi::Engine::Begin(1200, 800);
        Mi::Engine::StartMainLoop();
    }
    catch(const std::exception& e) {}
}