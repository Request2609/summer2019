#include"socket.h"

socketFd :: socketFd(const char* addr, const char*ip) {
    sockFd = socket(AF_INET, SOCK_STREAM, 0) ;
    struct sockaddr_in addr ;
    addr.sin_family = AF_INET ;
}   

int socketFd :: bindAddress(const char* addr, const char *ip) {
 
}
