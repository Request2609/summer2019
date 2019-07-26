#include "Channel.h"
channel :: channel() {
    sock = std::make_shared<socketFd>() ;
    events = 0 ;
    input.bufferClear() ;
    output.bufferClear() ;
    fd = -1 ;
}

//接收新连接
int channel::handleAccept(int fd) {
    //设置监听套接字
    sock->setListenFd(fd) ;
    //获取新客户端连接
    fd = sock->acceptSocket() ;
    //设置用户回调
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
        int n = handleRead() ;
        if(n < 0) {
            return ;
        }
    }

    if(events|EPOLLOUT) {
        handleWrite() ;
    }
}

//执行写回调
int channel :: handleWrite() {
    
    return 1 ;
}

//执行读回调
int channel :: handleRead() {
    
    int n = input.readBuffer(fd) ;
    if(n < 0) {
        return -1 ;
    }
    //消息设置好后，调用用户回调函数处理    
    if(input.getFlag() == true) {  
        readCallBack(this) ;
    }
    return 1 ;
}
