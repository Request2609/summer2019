#include"Connection.h"
#include"collectErr.h"
using namespace std :: placeholders ;

connection :: connection() {
    readCallBack = nullptr ;
    closeCallBack = nullptr ;
    writeCallBack = nullptr ;
    timeoutCallBack = nullptr ;
    //创建一个套接字新连接
    sock = std :: make_shared<socketFd>() ;          
    buffer.bufferClear() ;
}

connection :: ~connection() {
}

//给channel设置回调
void connection :: setCallBackToChannel(channel* channel_) {
    if(readCallBack != nullptr)
    channel_->setReadCallBack(readCallBack) ;
    if(writeCallBack != nullptr)
    channel_->setWriteCallBack(writeCallBack) ;
    if(timeoutCallBack != nullptr)
    channel_->setTimeoutCallBack(timeoutCallBack) ;
    if(closeCallBack != nullptr)
    channel_->setCloseCallBack(closeCallBack) ;
}

//关闭连接
void connection :: shutdown() {
    int connFd = sock->getAcceptSock() ;
    sock->shutdownWrite(connFd) ;
}

void connection :: setReadCallBack(callBack cb) {
    channel_.setReadCallBack(cb) ;
    readCallBack = std::move(cb) ;
}

void connection :: setCloseCallBack(callBack cb) {
    channel_.setCloseCallBack(cb) ;
    closeCallBack = cb ;
}

void connection :: setWriteCallBack(callBack cb) {
    channel_.setWriteCallBack(cb) ;
    writeCallBack = cb ;
}

void connection :: setTimeoutCallBack(callBack cb) {
    channel_.setTimeoutCallBack(cb) ;
    timeoutCallBack = cb ;
}

//创建一个新监听套接字，并将相应的channel中的fd设置一下
int connection :: createListenFd(int port) {
    sock->setAddr(port) ;   
    sock->bindAddress() ;
    sock->startListen()  ;
    int fd = sock->getListenSock() ;
    channel_.setFd(fd) ;
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

