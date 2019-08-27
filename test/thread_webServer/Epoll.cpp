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
    int eventNum ;
    struct epoll_event epFd_[200] ;
    int listenFd = loop->getListenFd() ; 
    try{
        eventNum = epoll_wait(epFd, epFd_, 200, timeout) ;
    }catch(exception e) {
        cout << e.what() ;
    }
    if(eventNum < 0) {
        cout << eventNum << "           错误：" << strerror(errno) << endl ;
        return -1 ;
    }
    //将活跃的事件全部加入到事件列表中
    for(int i=0; i<eventNum; i++) {
        int fd = epFd_[i].data.fd ;
        //要是还未注册的事件
        if(fd == listenFd) {
            //接收并注册该连接
            channel ch = loop->handleAccept() ;
            cout << "原来信息："<< ch.getFd() << endl ;
            //shared_ptr<channel>tmp = shared_ptr<channel>(&ch) ;
            //cout << "拷贝完成-------->" << tmp->getFd() << endl ;
            //将收集起来新连接
            loop->fillChannelList(&ch) ;
        }
    }
    return eventNum ;
}

int epOperation :: roundWait(loopInfo&loop, vector<channel>&actChl) {

    int ret = 0;
    ret = epoll_wait(epFd, &epFds[0], epFds.capacity(), -1) ;
    if(ret < 0) {
        return -1 ;
    }

    //同样收集活跃时间
    for(int i=0; i<ret; i++) {
        int fd = epFds[i].data.fd ;
        shared_ptr<channel> chl = loop.search(fd) ;
        actChl.push_back(*chl) ;
    }
    return ret ;
}
