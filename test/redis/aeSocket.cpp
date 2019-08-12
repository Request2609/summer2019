#include "aeSocket.h"

//创建套接字
int aeSocket :: anetCreateSocket() {
    sockFd = socket(AF_INET, SOCK_STREAM, 0) ;
    if(sockFd < 0) {
        std::cout << __FILE__ <<  "       " << __LINE__ << std::endl ;
        return -1 ;
    }
    int ret = setReuseAddr() ; 
    if(ret < 0) {
        return -1 ;
    }   
    return 1;
}

int aeSocket :: setReuseAddr() {
    
    int flag = 1 ;
    if(setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) < 0) {
        std::cout <<  __FILE__ << "     " << __LINE__ << std::endl ;
        return -1 ;
    }
    return  1 ;
}

int aeSocket :: setNoBlocking() {
    int old = fcntl(sockFd, F_GETFL) ;
    if(old < 0) {
        std :: cout << __FILE__ << "          " << __LINE__ << std::endl ;
        return -1 ;
    }
    int ret = old|O_NONBLOCK ;
    ret = fcntl(sockFd, ret) ;
    if(ret < 0) {
        std :: cout << __FILE__ << "              " << __LINE__ << std :: endl ;
        return -1 ;
    }
    std::cout << "设置成功！" << std:: endl ;
    return 1 ;
}

int aeSocket :: tcpServer(string port, string addr, int backLog) {

    serv.sin_family = AF_INET ;
    serv.sin_addr.s_addr = inet_addr(addr.c_str()) ;
    serv.sin_port = htons(atoi(port.c_str())) ;
    int ret = bind(sockFd, (struct sockaddr*)&addr, sizeof(addr)) ;
    if(ret < 0) {
        cout << __LINE__ <<  "              " << __FILE__ << endl ;
        return -1 ;
    }
    ret = listen(sockFd, backLog) ;
    if(ret < 0) {
        return -1 ;
    }
    return 1 ;
}

int aeSocket :: acceptClient() {
    int fd = accept(sockFd, NULL, NULL) ;
    return fd ;    
}
