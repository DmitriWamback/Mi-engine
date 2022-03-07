#ifndef MI_LIBRARIES_LOADED
    #error "Mi libraries not loaded, mibind cannot initialize"

#else
#ifdef MI_ENGINE_OPENGL

namespace mibind {

    void BindTextureToId(Mi::Texture tex, int id) {
        
    }

    void SetEntityTexture(Mi::Inheritable::Entity* entity, Mi::Texture tex) {

    }   
}

#endif
#endif