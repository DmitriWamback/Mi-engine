#if !defined(MI_COMPONENT_IMPLEMENTATION)
#define MI_COMPONENT_IMPLEMENTATION

namespace Mi {
    class RAttribute {
        
        std::vector< std::function<void()> > listeners;

        void Listen() {
            
        }
    };
}

#endif