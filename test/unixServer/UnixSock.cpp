#include <iostream>
#include "UnixSock.h"
#define PATH "/tmp/sss"

int uSocketFd :: bindAddr() {
    un.sun_family = AF_UNIX ;
    strcpy(un.sun_path, "/tmp/sss") ;
    size = sizeof(un.sun_family)+strlen(un.sun_path) ;
    if(bind(sockFd, (sockaddr*)&un, size) < 0) {
        std::cout << strerror(errno) <<std::endl  ;
        std::cout << __FILE__ << "     " << __LINE__ << std::endl ;
        return -1 ;
    }
    return 1 ;
}

int uSocketFd:: listenSock() {
    if(listen(sockFd, BACKLOG) < 0) {
        std::cout << __FILE__ << "       " << __LINE__ << std:: endl ;
        return -1 ;
    }
    return 1 ;
}

//接受连接
int uSocketFd :: acceptSock() {
    int cliFd ;
    cliFd = accept(sockFd, NULL, NULL) ;
    if(cliFd < 0) {
        std::cout << __FILE__ << "     " << std:: endl ;
        return -1 ;
    }
    return cliFd ;
}
