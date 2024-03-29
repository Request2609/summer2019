#include"Process.h"

void process :: append(struct epoll_event& ev) {
    channel tmp ;
    tmp.setEvents(ev.events) ;
    tmp.setFd(ev.data.fd) ;
    std::cout << "添加到队列：" << ev.data.fd << std::endl ;
    //网活跃事件表里面添加事件
    activeEvent.push(tmp) ; 
}

int process :: handleAccept() {
    //接收新连接
    int fd = uSock.acceptSock() ;
    if(fd < 0) {
        return -1 ;
    }
    std::cout << "接收新连接：" << fd<< std::endl ;
    //将新连接加入到epoll中
    ep->add(fd, READ) ;
    return 1 ;
}

int process :: bindListen() {
    int ret = uSock.bindAddr() ;
    if(ret < 0) {
        std:: cout << __FILE__ << "     " << std:: endl ;
        return -1 ;
    }
    
    ret = uSock.listenSock() ;
    if(ret < 0) {
        return -1 ;
    }

    ep->setProcess(this) ;
    ep->setListenFd(uSock.getFd()) ;
    return  uSock.getFd(); 
}

//添加到epoll中
int process :: addEpoll(int fd, int event) {
    //获取epoll句柄  
    ep->add(fd, event) ;
    return 1 ;
}


int process::setNoBlocking(int fd) {
    int old = fcntl(fd, F_GETFL) ;
    int news = old|O_NONBLOCK ;
    int ret = fcntl(fd, F_SETFL, news) ;
    if(ret < 0) {
        std::cout << __FILE__ << "     "<< __LINE__ << std::endl ;
        return -1 ;
    }   
    return 1 ;
}

void process :: start() {
    int fd = bindListen() ;
    setNoBlocking(fd) ;
    addEpoll(fd, READ) ;
    while(1) {
        int ret = ep->wait() ;
        if(ret < 0) {
            break ;
        }
        if(ret == 0) {
            continue ;
        }
        //处理活跃事件 thread in pool
        else {
            while(!activeEvent.empty()) {
                channel *chl =& (activeEvent.front()) ;
                int event = chl->getEvent() ;
                //将事件从队列中弹出
                activeEvent.pop() ;
                //从epoll中提前移除
                int fd = chl->getFd() ;
                std:: cout << "从epoll中删除：" << chl->getFd() << std::endl ;
                ep->del(chl->getFd()) ;
                std::cout << "当前队列中的事件数：" << std::endl ;
                if(event|EPOLLIN) {
                    std::cout << "事件可读：" << fd << std::endl ;
                    auto func = std:: bind(&process::handleRead, this, std::placeholders::_1) ;
                    pool.commit(func, chl) ;
                }
                //可写事件
                //开线程处理
                else if(event|EPOLLOUT) {
                    std::cout << "事件可写：" << fd << std::endl ;
                    auto func = std:: bind(&process::handleWrite, this, std::placeholders::_1) ;
                    pool.commit(func, *chl) ;
                  //  func(*chl) ;      
                }
            }
        }    
    }
}

//负责读事件
int process :: handleRead(channel* chl) {
    //获取Unix域套接字
    int ret =  chl->setConnFd() ;
    if(ret < 0) {
        std::cout << __FILE__ << "    "<< __LINE__ << std::endl ;
        return -1 ;
    }
    //将折个套接子加入到epoll中
   //处理事件
    readCall(*chl) ; 
    return 1 ;
}

//写事件处理
int process::handleWrite(channel& chl) {
    return 1 ;       
}


