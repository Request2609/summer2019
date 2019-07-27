#include "Channel.h"
channel :: channel() {
    sock = std::make_shared<socketFd>() ;
    events = 0 ;
    input.bufferClear() ;
    output.bufferClear() ;
    cliFd = -1 ;
}

//接收新连接
int channel::handleAccept(int servFd) {

    std :: cout << "接收新连接" << std::endl ;
    //设置监听套接字
    sock->setListenFd(servFd) ;
    //获取新客户端连接
    cliFd = sock->acceptSocket() ;
    //设置用户回调
    return cliFd ;
}
void channel :: setFd(int &fd) {
    this->cliFd = fd ;
}

int channel :: sendMsg() {
     return 1 ;  
}

int channel :: readMsg() {
    return 1 ;
}

int channel :: handleEvent() {
    if(events|EPOLLIN) { 
        int n = handleRead() ;
        if(n < 0) {
            return -1;
        }
        if(n == 0) {
            return 0 ;
        }
    }

    if(events|EPOLLOUT) {
        handleWrite() ;
    }
    return 1 ;
}

//执行写回调
int channel :: handleWrite() {
    
    return 1 ;
}

//执行读回调
int channel :: handleRead() {
    
    //读数据
    int n = input.readBuffer(cliFd) ;
    if(n < 0) {
        return -1 ;
    }
    ///读到0字节数据表明对端已经关闭连接
    if(n == 0) {
        return 0 ;
    }
    //消息设置好后，调用用户回调函数处理    
    if(input.getCanProcess() == true) {  
        readCallBack(this) ;
    }
    return 1 ;
}
