#if !defined(MI_COMPONENT_IMPLEMENTATION)
#define MI_COMPONENT_IMPLEMENTATION

namespace Mi {
    class RAttribute {
        
        std::vector< std::function<void()> > listeners;

        void Listen() {
            
        }

        template<class T>
        T CastTo() {
            return dynamic_cast<T>(this);
        }
    };
}

#endif