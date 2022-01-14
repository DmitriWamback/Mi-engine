#include "MiCore/engine.h"

int main() {

    try {
        vmi_engine::vMiEngineBegin(1200, 800);
        vmi_engine::vMiEngineStartMainLoop();
    }
    catch(const std::exception& e) {}
}