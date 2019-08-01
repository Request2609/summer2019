#include "Epoll.h"

int epOperation:: wait() {
    int ret = epoll_wait(epFd, &epFds[0], epFds.capacity(), -1) ;
    for(int i=0; i<ret; i++) {
        int fd = epFds[i].data.fd ;
        //有新连接
        if(fd == listenFd) {
            int ret = pro->handleAccept() ;
            if(ret < 0) {
                return -1 ;
            }
            continue ;
        }
        if(epFds[i].events|EPOLLOUT) {
            pro->append(epFds[i]) ;
        }
        if(epFds[i].events|EPOLLIN) {
            pro->append(epFds[i]) ;
        }
    }
    return ret ;
}

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

