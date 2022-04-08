#include <iostream>
#include "server.h"

int main() {

    Mi::MiT::InitializeMiTServer();
    while (1) {
        Mi::MiT::Read();
    }
}