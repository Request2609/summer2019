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
int epOperation :: wait(eventLoop* loop, int64_t timeout) {
    
    int listenFd = loop->getListenFd() ; 
    int eventNum = epoll_wait(epFd, &epFds[0], epFds.capacity(), timeout) ;
    //将活跃的事件全部加入到事件列表中
    for(int i=0; i<eventNum; i++) {
        int fd = epFds[i].data.fd ;
        //要是还未注册的事件
        if(fd == listenFd) {
            //接收并注册该连接
            channel ch = loop->handleAccept() ;
            //将收集起来新连接
            loop->fillChannelList(&ch) ;
        }
    }
    return eventNum ;
}

int epOperation :: roundWait(loopInfo&loop, vector<channel>&actChl) {
    struct epoll_event ev[4096] ; 
    int ret = 0;
    do {
        ret = epoll_wait(epFd, ev, 4096, -1) ;
        if(ret < 0) {
            cout <<"错误码：" << errno << "     " << __FILE__ <<"        "<< strerror(errno)<< "      " << __LINE__ << endl ;
            return -1 ;
        }
        if(ret > 0) {
            break ;
        }
    }while(ret < 0 && errno == EINTR) ;

    //同样收集活跃时间
    for(int i=0; i<ret; i++) {
        int fd = ev[i].data.fd ;
        shared_ptr<channel> chl = loop.search(fd) ;
        actChl.push_back(*chl) ;
    }
    return ret ;
}
