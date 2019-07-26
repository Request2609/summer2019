#include"EventLoop.h" 

eventLoop :: eventLoop() {
    //创建一个epoll
    epPtr = std::make_shared<epOperation>() ;
    quit = false ;
}


void eventLoop :: loop() {
    //将conn加入到epoll中 
    int events = clList[servFd].getEvents() ;
    //将当前的服务加入到epoll中
    epPtr->add(servFd, events) ;
    while(!quit) {
        //等待事件
        int ret = epPtr->wait(this, -1) ;
        if(ret < 0) {
            quit = true ;
        }
        //epoll返回０，没有活跃事件
        else if(ret == 0) {
            //可以设置定时器
        }
        else {
            //有事件发生
            for(channel channel: activeChannels) {
                //处理事件
                channel.handleEvent() ;
            }
        }
    }   
}

//将活跃的事件加入到活跃事件表中
int eventLoop :: fillChannelList(channel* chl) {
    activeChannels.push_back(*chl) ;
}

//值有监听套接字拥有connection
//向loop中添加新的conn.将这个连接加入到epoll中
void eventLoop :: addConnection(connection* con) {
    conn = con ;
    channel* channel_ = conn->getChannel() ;
    int fd = channel_->getFd() ;
    servFd = fd ;
    //将这个服务器监听套接字加入到epoll中，只负责监听可读事件，LT模式
    channel_->setEvents(READ) ;
    //将fd和channel作为键值存入channelMap中
    clList[fd] = *channel_ ;
}

//根据描述符搜索channel对象
channel* eventLoop :: search(int fd) {
    std::map<int, channel> :: iterator it = clList.find(fd) ;
    if(it == clList.end()) {
        return NULL ;
    }
    else {
        return &(it->second) ;
    }
} 

//接收连接并添加channel
void eventLoop :: handleAccept() {
    channel tmp;
    //创建新连接
    int conFd = tmp.handleAccept(servFd) ;
    //为channel设置回调
    conn->setCallBackToChannel(&tmp) ;
    //将channel加入到当前loop的列表中
    clList[conFd] = tmp ;
}