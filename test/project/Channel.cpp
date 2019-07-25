#include "Channel.h"
channel :: channel() {
    sock = std::make_shared<socketFd>() ;
    events = 0 ;
    input.bufferClear() ;
    output.bufferClear() ;
    fd = -1 ;
}

int channel::handleAccept(int fd) {
    //设置监听套接字
    sock->setListenFd(fd) ;
    //获取新客户端连接
    fd = sock->acceptSocket() ;
    return fd ;
}
void channel :: setFd(int &fd) {
    this->fd = fd ;
}

int channel :: sendMsg() {
     return 1 ;  
}

int channel :: readMsg() {
    return 1 ;
}

void channel :: handleEvent() {
    if(events|EPOLLIN) {    
        handleWrite() ;
    }

    if(events|EPOLLOUT) {
        handleRead() ;
    }
}

//执行写回调
int channel :: handleWrite() {
    
    return 1 ;
}

//执行读回调
int channel :: handleRead() {
    input.readBuffer(fd) ;
    return 1 ;
}
