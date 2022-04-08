#include <iostream>
#include <vector>
#include <map>

namespace MITI {

    class MITISocketServer {
    public:

        static MITISocketServer CreateLocalhost() {

            MITISocketServer s = MITISocketServer();
            return s;
        }

        std::map<int, const char*> HasContent() {

            std::map<int, const char*> result;
            result[0] = "none";
            return result;
        }

        float* ReadVertices() {

            std::map<int, const char*> r = HasContent();
            if (std::string(r[0]) != "none") {
                
            }

            return nullptr;
        }
    };
}