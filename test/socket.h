#pragma once
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<>
#include<netinet/in.h>

class socketFd
{
public:
    socketFd(const char* addr, const char*ip);
    ~socketFd() {close(sockFd) ;} ;
public :
    int bindAddress(const char* addr, const char* ip) ;
    int startListen() ;
    int setReuseAddr() ;
    int shutDownWrite() ;
    int acceptSocket(int sockFd) ;

private:
    int sockFd ;
};

