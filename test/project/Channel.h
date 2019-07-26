#pragma once
#include <iostream>
#include <functional>
#include <sys/epoll.h>
#include <memory>
#include "Socket.h"
#include "Buffer.h"
using namespace std :: placeholders ;
enum {
    READ = EPOLLIN,
    WRITE = EPOLLOUT,
    ATOMIC= EPOLLONESHOT ,
    ERROR = EPOLLERR,
    ET = EPOLLET 
} ;
//事件分发
class channel
{
    typedef std::function<void(channel* chl)> callBack ;
public:
    channel() ;
    ~channel() {}
public :
    int getFd() {
        return fd ;
    }
    void setFd(int& fd) ;   
    void setReadCallBack(callBack& cb) {
        readCallBack = cb ;
    }
    void setWriteCallBack(callBack& cb) {
        writeCallBack = cb ;
    }

    void setCloseCallBack(callBack& cb) {
        closeCallBack = cb ;
    }
    void setTimeoutCallBack(callBack& cb) {
        timeoutCallBack = cb ;
    }
    //判断是否收到了一段消息完整的消息"\r\n"结束
    void handleEvent() ;
    int handleWrite() ;
    int handleRead() ;
    int handleAccept(int fd) ;
    //设置channel监听的事件类型
    void setEvents(int event) { events = event ;}
    void enableReading() {  events|=EPOLLIN ;}
    void enableWriting() {  events|=EPOLLOUT ;}
    void disableRead() { events &= ~EPOLLIN ; }
    void disableWrite() { events &= ~EPOLLOUT ; } 
    int getEvents() { return events ; }
    int sendMsg() ;
    int readMsg() ;
    Buffer* getReadBuffer() { return  &input ;}
    Buffer* getWriteBuffer() { return  &output ;}
private :
    int flag = 0 ;
    //设置一个标志，是否要继续读
    //感兴趣的事件
    int events ;
    //保存监听套接字信息
    std :: shared_ptr<socketFd> sock ;
    //读回调
    callBack readCallBack ;
    //写
    callBack writeCallBack ;
    //关闭回调
    callBack closeCallBack ;
    //超时
    callBack timeoutCallBack ;
    //写完成关闭连接
    callBack writeCompleteCallBack ;
    //写缓冲区
    Buffer input ;
    //度缓冲区
    Buffer output ;
    //要是监听套接字的话，就是监听套接字的文件描述符
    //否则就是目标客户端的fd
    int fd ;
};

