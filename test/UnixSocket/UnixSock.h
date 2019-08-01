#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define BACKLOG 1024 
//构造Unix域套接字
class uSocketFd {

public :
    uSocketFd() { sockFd = socket(AF_UNIX, SOCK_STREAM, 0) ;}
    ~uSocketFd() {close(sockFd) ;}
public :
    int getFd() { return sockFd ; }
    int bindAddr() ;
    int listenSock() ;
    int acceptSock() ;
private :
    int size ;
    struct sockaddr_un un;
    int sockFd ;
} ;

