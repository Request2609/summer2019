#include "Epoll.h"
#include "collectErr.h"

void epOperation :: add(int fd, int events) {
    struct epoll_event ev ;
    ev.data.fd = fd ;
    ev.events = events ;
    if(epoll_ctl(epFd, EPOLL_CTL_ADD, fd, &ev) < 0) {
        writeErr(__FILE__, __LINE__) ;
        return ;
    }
    if(++ fds > nfds) {
        nfds *= 2 ;
        epFds.reserve(nfds) ;
    }
}

//修改事件监听类型
void epOperation :: change(int fd, int events) {
    struct epoll_event ev ;
    ev.data.fd = fd ;
    ev.events = events ;
    if(epoll_ctl(epFd, EPOLL_CTL_MOD, fd, &ev) < 0) {
        writeErr(__FILE__, __LINE__) ;
        return ;
    }
}

void epOperation :: del(int fd) {
    if(epoll_ctl(epFd, EPOLL_CTL_DEL, fd, NULL) < 0){
        writeErr(__FILE__, __LINE__) ;
        return  ;
    }
    fds -- ;
}

//将活跃的事件全加入到clList
int epOperation :: wait(eventLoop* loop, int64_t timeout) {

    int listenFd = loop->getListenFd() ; 
    int eventNum = epoll_wait(epFd, &epFds[0], epFds.capacity(), timeout) ;
    //将活跃的事件全部加入到事件列表中
    for(int i=0; i<eventNum; i++) {
        int fd = epFds[i].data.fd ;
        //要是还未注册的事件
        if(fd == listenFd) {
            //注册该连接
            loop->handleAccept() ;
        }

        channel* ch = loop->search(fd) ;
        if(ch == NULL) {
            writeErr(__FILE__, __LINE__) ;
            return -1;
        }
        else {
            //设置事件类型
            ch->setEvents(epFds[i].events) ;
            loop->fillChannelList(ch) ;   
        }
    }
    return eventNum ;
}
