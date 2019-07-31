#ifndef _SOCKET_H_
#define _SOCKET_H_
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#define BACKLOG 500
class socketFd
{
public:
    socketFd() ;
    socketFd(const char* port) ;
    socketFd(const char* addr, const char*port);
    socketFd(int port) ;
    ~socketFd() {
        close(connFd) ;
        close(sockFd) ;
    } ;

public :
    void setListenFd(int fd) { sockFd = fd ; }
    void setConnFd(int fd) { connFd = fd ; }
    //设置地址
    int setAddr(int port) ;
    int setAddr(const char* ip, const char* port) ;
    int setAddr(const char* port) ;
    //套接字绑定地址
    int bindAddress() ;
    //开始监听
    int startListen() ;
    //地址复用
    int setReuseAddr() ;
    //接收新连接
    int acceptSocket() ;
    //获取监听套接字
    int getListenSock() ;
    //获取接收到的新连接套接字
    int getAcceptSock() ;
    //社会套接字非阻塞
    int setNoBlocking(int fd) ;
    //关闭读端
    void shutdownWrite(int fd) ;
private:
    int sockFd = -1 ;
    int connFd =  -1 ;
    struct sockaddr_in sockAddr ;
};

#endif
