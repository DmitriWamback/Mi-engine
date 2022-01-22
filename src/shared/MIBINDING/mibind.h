#ifndef MI_LIBRARIES_LOADED
    #error "Mi libraries not loaded, mibind cannot initialize"

#else
#ifdef MI_ENGINE_OPENGL

namespace mibind {

    void BindTextureToId(mi::Texture tex, int id) {
        
    }

    void SetEntityTexture(mi_inheritable::Entity* entity, mi::Texture tex) {

    }   
}

#endif
#endif