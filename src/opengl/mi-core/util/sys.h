#if !defined(MI_OPENGL_RENDER_SYSTEM)
    #define MI_OPENGL_RENDER_SYSTEM


    namespace Mi {

        namespace Enum {
            enum SYSTYPE {
                SYS_PARTICLE
            };
        }

        class System { 
        public:

            Mi::Enum::SYSTYPE type;

            template<class T>
            T CastTo() {
                return dynamic_cast<T>(*this);
            }

            void Update() {

            }
        };
    }

#endif