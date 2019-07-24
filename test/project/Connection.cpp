#include"Connection.h"
#include"collectErr.h"

connection :: connection() {
    //创建一个套接字新连接
    sock = std :: make_shared<socketFd>() ;          
    buffer.bufferClear() ;
}

connection :: ~connection() {
}


//关闭连接
void connection :: shutdown() {
    int connFd = sock->getAcceptSock() ;
    sock->shutdownWrite(connFd) ;
}

//发送消息
void connection :: sendMessage(Buffer* buffer) {
             
}
void connection :: setReadCallBack(callBack& cb) {
    this->readCallBack = cb ;
}

void connection :: setCloseCallBack(callBack& cb) {
    this->closeCallBack = cb ;
}

void connection :: setWriteCallBack(callBack& cb) {
    this->writeCallBack = cb ;
}

void connection :: setTimeoutCallBack(callBack& cb) {
    this->timeoutCallBack = cb ;
}

//创建一个新监听套接字
int connection :: createListenFd(int port) {
    sock->setAddr(port) ;     
    sock->bindAddress() ;
    sock->startListen()  ; 
    return 1 ;
} ;

//接收tcp新连接，先判断新连接的监听套接字存不存在
int connection :: doAccept() {
    int servFd = sock->getListenSock() ;
    if(servFd == -1) {
        writeErr(__FILE__, __LINE__) ;
        return -1 ;
    }   
    //存在的话
    int connFd = sock->acceptSocket() ;
    //接受连接失败;
    if(connFd < 0) {
        writeErr(__FILE__, __LINE__) ;   
        return -1 ;
    }
    this->fd = connFd ;
    return 1 ;
}   

