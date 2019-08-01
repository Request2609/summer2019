#ifndef _EPOLL_H_
#define _EPOLL_H_
#include <sys/epoll.h>
#include <vector>
#include <unistd.h>
#include <iostream>
#include "Process.h"
#include "ThreadPool.h"
class eventLoop ;
class process ;
enum{
    READ=EPOLLIN , WRITE=EPOLLOUT
};
class epOperation {
public :
    epOperation():fds(0),nfds(200) {
        epFd = epoll_create(1) ;
        std::cout <<"EPOLLFD:" << epFd << std::endl ;
       //设置了epfds的capacity大小
        epFds.reserve(nfds) ;
    }   
    ~epOperation() { close(epFd) ; }
public :
    
    void setProcess(process* p) { pro = p ;}
    void setListenFd(int fd) { listenFd = fd ; }
    int getListenFd() { return listenFd ; }
    int getEpFd() {return epFd ;}
    void add(int fd, int events) ;
    void change(int fd, int events) ;
    void del(int fd) ;
    int wait() ;
private :
    threadPool* pool ;
    process* pro ;
    int epFd ;
    int listenFd ;
    //帮助更新epoll中的事件数量
    int fds ;
    int nfds ;
    std :: vector<struct epoll_event> epFds ;
};
#endif
