#include "miti/core.h"

int main() {
    std::cout << "HELLO" << std::endl;
    MITI::Core::InitializeMITI(1200, 800);
    MITI::Core::StartMainLoop();
    std::cout << "HELLO" << std::endl;
}