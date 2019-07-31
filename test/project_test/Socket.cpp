#include "Socket.h"

socketFd :: socketFd() {
    sockFd = socket(AF_INET, SOCK_STREAM, 0) ;
    if(sockFd < 0) {
        std::cout<<__FILE__<<__LINE__<<std::endl; ;
        return ;
    }
}


socketFd :: socketFd(int port) {

    sockFd = socket(AF_INET, SOCK_STREAM, 0) ;
    if(sockFd < 0) {
        std::cout<<__FILE__<<__LINE__<<std::endl; ;
        return ;
    }
    bzero(&sockAddr, sizeof(sockAddr)) ;
    sockAddr.sin_family = AF_INET ;
    sockAddr.sin_port = htons(port) ;
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY) ;
}

socketFd :: socketFd(const char* port) {
    sockFd = socket(AF_INET, SOCK_STREAM, 0) ;
    if(sockFd < 0) {
        std::cout<<__FILE__<<__LINE__<<std::endl; ;
        return ;
    }
    bzero(&sockAddr, sizeof(sockAddr)) ;
    sockAddr.sin_family = AF_INET ;
    sockAddr.sin_port = htons(atoi(port)) ;
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY) ;
}

socketFd :: socketFd(const char* addr, const char*port) {
    
    sockFd = socket(AF_INET, SOCK_STREAM, 0) ;
    if(sockFd < 0) {
        std::cout<<__FILE__<<__LINE__<<std::endl; ;
        return ;
    }

    bzero(&sockAddr, sizeof(sockAddr)) ;
    sockAddr.sin_family = AF_INET ;
    sockAddr.sin_port = htons(atoi(port)) ;
    sockAddr.sin_addr.s_addr = inet_addr(addr) ;
}   

int socketFd :: setAddr(int port) {
    bzero(&sockAddr, sizeof(sockAddr)) ;
    sockAddr.sin_family = AF_INET ;
    sockAddr.sin_port = htons(port) ;
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY) ;
    return 1 ;
}

//设置地址
int socketFd :: setAddr(const char* ip, const char* port) {
    assert(ip != NULL) ;
    assert(port != NULL) ;

    bzero(&sockAddr, sizeof(sockAddr)) ;
    sockAddr.sin_family = AF_INET ;
    sockAddr.sin_port = htons(atoi(port)) ;
    sockAddr.sin_addr.s_addr = inet_addr(ip) ;
    return 1 ;
}

int socketFd :: setAddr(const char* port) {
    assert(port != NULL) ;
    bzero(&sockAddr, sizeof(sockAddr)) ;
    sockAddr.sin_family = AF_INET ;
    sockAddr.sin_port = htons(atoi(port)) ;
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY) ;
    return 1 ;
}

void socketFd :: shutdownWrite(int fd) {
    int ret = shutdown(fd, SHUT_WR) ;
    if(ret < 0) {
        std::cout<<__FILE__<<__LINE__<<std::endl; ;
        return ;
    }
}

int socketFd :: getListenSock() {
    return sockFd ;
}

int socketFd :: getAcceptSock() {
    return connFd ;
}

int socketFd :: setReuseAddr() {
    int flag = 1 ;
    if(sockFd < 0) {
        std::cout<<__FILE__<<__LINE__<<std::endl; ;
        return -1;;
    }
    int ret = setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) ;
    if(ret < 0) {
        std::cout<<__FILE__<<__LINE__<<std::endl; ;
        return -1;
    }
    return 1 ;
}

int socketFd :: bindAddress() {
    assert(sockFd != -1) ;
    if(bind(sockFd, (struct sockaddr*)&sockAddr, sizeof(sockAddr))< 0) {
        std::cout<<__FILE__<<__LINE__<<std::endl; ;
        return -1 ;
    }
    return 1 ;
}    

int socketFd :: acceptSocket() {

    assert(sockFd != -1) ;
    int connFd = accept(sockFd, NULL, NULL) ;
    if(connFd < 0) {
        std::cout<<__FILE__<<__LINE__<<std::endl; ;
        return -1 ;
    }
    std::cout << "接受的connfd: " << connFd << std::endl ;
    this -> connFd = connFd ;
    return connFd ;
}

int socketFd :: startListen() {
    assert(sockFd != -1) ;
    if(listen(sockFd, BACKLOG) < 0) {
        std::cout<<__FILE__<<__LINE__<<std::endl; ;
        return -1 ;
    }
    return 1 ;
}

int socketFd :: setNoBlocking(int fd) {
    std::cout << fd << std::endl ;
    int old = fcntl(fd, F_GETFL, 0) ;
    assert(old != -1) ;
    int newA = old|O_NONBLOCK ;
    int ret = fcntl(fd, F_SETFL, newA) ;
    if(ret < 0) {
        std::cout<<__FILE__<<__LINE__<<std::endl; ;
        return -1 ;
    }
    return 1 ;
}


