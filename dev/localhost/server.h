#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>
#include <arpa/inet.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 

#define MI_LOCALHOST_READBYTES_SIZE 4096

namespace Mi { namespace MiT {

    int server;
    int mitfd;

    struct sockaddr_in addr;

    void InitializeMiTServer() {
        server = socket(AF_INET, SOCK_STREAM, 0);
        bzero(&addr, sizeof(addr));

        addr.sin_family         = AF_INET;
        addr.sin_addr.s_addr    = htons(INADDR_ANY);
        addr.sin_port           = htons(6060);

        bind(server, (struct sockaddr*)&addr, sizeof(addr));
        listen(server, 10);

        std::cout << "Waiting for a connection..." << '\n';
        mitfd = accept(server, (struct sockaddr*)NULL, NULL);
    }

    char* Read() {
        char inputBuffer[MI_LOCALHOST_READBYTES_SIZE];
        bzero(inputBuffer, MI_LOCALHOST_READBYTES_SIZE);

        if (mitfd != 0) {
            read(mitfd, inputBuffer, MI_LOCALHOST_READBYTES_SIZE);
            std::cout << inputBuffer << '\n';
        }

        return inputBuffer;
    }
}}