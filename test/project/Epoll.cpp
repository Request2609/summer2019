#include "Epoll.h"

void epOperation :: add(int fd, int events) {
    struct epoll_event ev ;
    ev.data.fd = fd ;
    ev.events = events ;
    if(epoll_ctl(epFd, EPOLL_CTL_ADD, fd, &ev) < 0) {
        std :: cout << __FILE__ << "   " << __LINE__ << std :: endl ;
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
        std :: cout << __FILE__ << "   " << __LINE__ << std :: endl ;
        return ;
    }
}

void epOperation :: del(int fd) {
    if(epoll_ctl(epFd, EPOLL_CTL_DEL, fd, NULL) < 0){
        std :: cout << __FILE__ << "   " << __LINE__ << std :: endl ;
        return  ;
    }
    fds -- ;
}

//将活跃的事件全加入到clList
std::vector<channel> epOperation :: wait(eventLoop* loop, int64_t timeout) {
    std::vector<channel>chl ;
    int listenFd = loop->getListenFd() ; 
    int eventNum = epoll_wait(epFd, &epFds[0], epFds.capacity(), timeout) ;
    //将活跃的事件全部加入到事件列表中
    for(int i=0; i<eventNum; i++) {
        int fd = epFds[i].data.fd ;
        //要是还未注册的事件
        if(fd == listenFd) {
            printf("接收新连接：%d\n",fd) ;
            //接收并注册该连接
            //将新连接注册到epoll中,并产生新的loop事件循环
            chl.emplace_back(loop->handleAccept()) ;
        }
/*
        //无论那种事件，否加入到活跃列表
=======

        //无论那种事件，加入到活跃列表
>>>>>>> 7f5767318cdf45305c3acc000c256e83bf9e4903
        if(fd != listenFd) {
            channel* ch = loop->search(fd) ;
            if(ch == NULL) {
                std :: cout << __FILE__ << "   " << __LINE__ << std :: endl ;
                return -1;
            }
            else {
                //添加事件，还没进线程，不加锁:
                loop->fillChannelList(ch) ;   
            }
        }*/
    }
    return chl ;
}

int epOperation :: poll() {
    int ret =  epoll_wait(epFd, &epFds[0], epFds.capacity(), -1) ;
    if(ret < 0) { 
        return -1 ;
    }
    for(int i=0; i<ret; i++) {
        int fd = epFds[i].data.fd ;
        
    }   
}
