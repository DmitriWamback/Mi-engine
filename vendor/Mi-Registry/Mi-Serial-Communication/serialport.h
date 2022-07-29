#include <iostream>

namespace Mi { namespace Hardware {

    class Serialport {
    public:

        const char* p_name; // Serial port name
        int p_location;     // Serial port file
        int p_baud;         // Serial port baud
        
        static Serialport Open(const char* port, int baud) {
            
            Serialport p;
            p.p_name = port;
            p.p_baud = baud;
            p.p_location = open(port, O_RDWR | O_NOCTTY | O_SYNC);
            int status = Mi::Hardware::SetBaudRate(p.p_location, p.p_baud);

            if (status != 0) std::cout << std::string("Could not set baud rate of serial port: ").append(port) << std::endl;

            return p;
        }

        void Reopen(int baud) {
            int status = Mi::Hardware::SetBaudRate(p_location, p_baud);
            if (status != 0) std::cout << std::string("Could not set baud rate of serial port: ").append(p_name) << std::endl;
        }

        std::string Read(int bufsize) {
            char result[bufsize];
            memset(&result, '\0', bufsize);

            int nbchars = 0, spot = 0;
            char buf = '\0';

            do {
                nbchars = read(p_location, &buf, 1);
                sprintf(&result[spot], "%c", buf);
                spot += nbchars;
            }
            while (buf != '\r' && nbchars > 0);

            return std::string(result);
        }

        void Write(const char* message) {
            int msglen = strlen(message);
            write(p_location, message, msglen);
        }
    };
}}