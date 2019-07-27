#pragma once
#include <sys/epoll.h>
#include <vector>
#include <unistd.h>
#include "EventLoop.h"

class epOperation {
public :
    epOperation():fds(0),nfds(20) {
        epFd = epoll_create(1) ;
        //设置了epfds的capacity大小
        epFds.reserve(nfds) ;

    }   
    ~epOperation() { close(epFd) ; }
    
public :
    int wait(eventLoop* loop, int64_t timeout) ;
    void add(int fd, int events) ;
    void change(int fd, int events) ;
    void del(int fd) ;
private :
    int epFd ;
    //帮助更新epoll中的事件数量
    int fds ;
    int nfds ;
    std :: vector<struct epoll_event> epFds ;
};
