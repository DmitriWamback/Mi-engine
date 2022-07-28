#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

namespace Mi { namespace Hardware {

    int SetBaudRate(int port, int baud) {

        struct termios tty;
        if (tcgetattr(port, &tty) != 0) {
            std::cout << "Serial port could not be opened" << std::endl;
            return -1;
        }

        cfsetospeed(&tty, baud);
        cfsetispeed(&tty, baud);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; 
        tty.c_iflag &= ~IGNBRK;
        tty.c_lflag = 0;                      
        tty.c_oflag = 0;
        tty.c_cc[VMIN]  = 0;
        tty.c_cc[VTIME] = 5;

        tty.c_iflag &= ~(IXON | IXOFF | IXANY);
        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
        tty.c_cflag &= ~(PARENB | PARODD);

        tty.c_cflag |= 0;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;
        if (tcsetattr (port, TCSANOW, &tty) != 0) {
            return -1;
        }

        return 0;
    }   
}}