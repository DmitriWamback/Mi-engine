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
#include <thread>

#define READBYTES_SIZE 4096

namespace MITI {

    class MITISocketServer {
    public:

        int ServerFD; // server
        int MitiConn; // connection
        struct sockaddr_in SocketAddress;
        bool isConnected;

        // Creates a Socket Server binded at localhost:6060
        static MITISocketServer CreateLocalhost() {

            MITISocketServer s = MITISocketServer();
            s.ServerFD = socket(AF_INET, SOCK_STREAM, 0);
            bzero(&s.SocketAddress, sizeof(s.SocketAddress));

            s.SocketAddress.sin_family          = AF_INET;
            s.SocketAddress.sin_addr.s_addr     = htons(INADDR_ANY);
            s.SocketAddress.sin_port            = htons(6060);
            
            bind(s.ServerFD, (struct sockaddr*)&s.SocketAddress, sizeof(s.SocketAddress));
            listen(s.ServerFD, 10);
            return s;
        }

        ~MITISocketServer() { }

        void __wait() {
            while (true) {
                std::cout << "Host: localhost:6060\n";
                std::cout << "Waiting for a connection...\n";
                MitiConn = accept(ServerFD, (struct sockaddr*)NULL, NULL);
                std::cout << "Connection Accepted!\n";
                isConnected = true;
            }
        }

        void WaitConnection() {
            std::thread obj = std::thread(&MITISocketServer::__wait, this);
            obj.detach();
        }

        std::map<int, const char*> HasContent() {
            
            std::map<int, const char*> result;
            char buf[READBYTES_SIZE];
            bzero(buf, READBYTES_SIZE);

            int err = 0;
            if (isConnected) {
                err = recv(MitiConn, buf, READBYTES_SIZE, 0);
            }
            if (err == 0 && isConnected) {
                isConnected = false;
                WaitConnection();
                result[0] = "none";
                return result;
            }
            if (!isConnected) {
                result[0] = "none";
                return result;
            }
            result[0] = buf;
            return result;
        }

        std::string Read() {

            std::map<int, const char*> r = HasContent();
            return std::string(r[0]);
        }

    private:
    };
}