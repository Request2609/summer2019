#pragma once
#include <sys/un.h>
#include <sys/socket.h>
#include "Buffer.h"
#include "Process.h"
#include "Epoll.h"
struct logBuf ;

class channel
{
public:
    channel() :flag(-1), cliFd(0), event(EPOLLIN){}
    ~channel() {}
public :
    int setConnFd() ;
    void setFlag(int flag) { this->flag = flag ; }
    int getFlag() { return flag ; }
    int getEvent() { return event ; }
    void setEvents(int event) { this->event=event ; }
    channel* getChannel() { return this; }
    void setFd(int cliFd) { this->cliFd = cliFd ; }
    int getFd() { return cliFd ; }
    int getConnFd() { return connFd ; }
    logBuf* getBuf() { return buf ; }
private:

    int flag ;
    //web服务器请求对应的套接字
    int connFd ;
    //该channel对应的fd
    int cliFd ;
    //该channel对应的事件　
    int event ;
    logBuf* buf ;
    //该channel对应的输出缓冲区
};

