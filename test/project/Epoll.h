#ifndef _EPOLL_H_
#define _EPOLL_H_
#include <sys/epoll.h>
#include <vector>
#include <unistd.h>
#include "EventLoop.h"
class eventLoop ;
class epOperation {
public :
    epOperation():fds(0),nfds(200) {
        epFd = epoll_create(1) ;
       //设置了epfds的capacity大小
        epFds.reserve(nfds) ;
    }   
    ~epOperation() { close(epFd) ; }
public :
    int getEpFd() {return epFd ;}
    std::vector<channel>  wait(eventLoop* loop, int64_t timeout) ;
    void add(int fd, int events) ;
    void change(int fd, int events) ;
    void setMutex(std::mutex* mut) {this->mute = mut ;} 
    void del(int fd) ;
    int poll() ;
private :
    std::mutex* mute ;
    int epFd ;
    //帮助更新epoll中的事件数量
    int fds ;
    int nfds ;
    std :: vector<struct epoll_event> epFds ;
};

#endif
