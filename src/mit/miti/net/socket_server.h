#include <iostream>
#include <vector>
#include <map>

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>
#include <arpa/inet.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 

namespace MITI {

    class MITISocketServer {
    public:

        int ServerFD; // server
        int MitiConn; // connection
        struct sockaddr_in SocketAddress;

        // Creates a Socket Server binded at localhost:6060
        static MITISocketServer CreateLocalhost() {

            MITISocketServer s = MITISocketServer();
            s.ServerFD = socket(AF_INET, SOCK_STREAM, 0);
            bzero(&s.SocketAddress, sizeof(s.SocketAddress));

            s.SocketAddress.sin_family          = AF_INET;
            s.SocketAddress.sin_addr.s_addr     = htons(INADDR_ANY);
            s.SocketAddress.sin_port            = htons(6060);
            
            bind(s.ServerFD, (struct socketaddr*)&s.SocketAddress, sizeof(s.SocketAddress));
            listen(s.ServerFD, 10);
            return s;
        }

        void Listen() {
            MitiConn = accept(server, (struct sockaddr*)NULL, NULL);
        }

        std::map<int, const char*> HasContent() {

            std::map<int, const char*> result;
            result[0] = "none";
            return result;
        }

        float* ReadVertices() {

            std::map<int, const char*> r = HasContent();
            if (std::string(r[0]) != "none") { }

            return nullptr;
        }        
    };
}