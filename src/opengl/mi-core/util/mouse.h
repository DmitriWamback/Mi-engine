namespace Mi { namespace Enum {

    enum MOUSESTATE {
        LOCKED = 0x0d8E,
        FREE = 0x0f8F
    };
}}

namespace Mi { namespace Engine {

    void MiSetCursorState(Mi::Enum::MOUSESTATE mouseState) {

        if (mouseState == Mi::Enum::LOCKED) {

        }
        if (mouseState == Mi::Enum::FREE) {

        }
    }
}}