namespace mi_enum {

    enum MOUSESTATE {
        LOCKED = 0x0d8E,
        FREE = 0x0f8F
    };
}

namespace mi_engine {

    void MiSetCursorState(mi_enum::MOUSESTATE mouseState) {

        if (mouseState == mi_enum::LOCKED) {

        }
        if (mouseState == mi_enum::FREE) {

        }
    }
}