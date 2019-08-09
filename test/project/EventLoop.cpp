#include"EventLoop.h" 

eventLoop :: eventLoop() {
    //创建一个epoll
    epPtr = std::make_shared<epOperation>() ;
    quit = false ;
}

int eventLoop :: clearCloseChannel(channel chl) {
    //获取到fda
    int fds = chl.getFd() ;
    epPtr->del(fds) ;
    close(fds) ;
    std::map<int, channel>::iterator iter ; 
    iter = clList.find(fds) ; 
    if(iter != clList.end()) {
        return -1 ;
    }
    clList.erase(iter) ;
    return 1 ;
}

int eventLoop :: clearCloseChannel(std::vector<channel>&list_) {
    //从epoll中删除套接字
    std::map<int, channel>::iterator iter ;
    for(channel chl:list_) {
        int fds = std::move(chl.getFd()) ;
        epPtr->del(fds) ;
        close(fds) ;
        //从map列表中找到并删除
        iter = clList.find(fds) ;
        if(iter == clList.end()) {
            return -1 ;
        }
        clList.erase(iter) ;
    }
    return 1 ;
}


void eventLoop :: loop() {
    //将conn加入到epoll中 
    int events = clList[servFd].getEvents() ;
    //将当前的服务加入到epoll中
    epPtr->add(servFd, events) ;
    while(!quit) {
        //等待事件
<<<<<<< HEAD
        std::vector<channel>chl = epPtr->wait(this, -1) ;
        epOperation ep ;
        
        //将事件列表加入到线程池中
    /*    if(ret < 0) {
=======
        int ret = -1 ;
        {
            ret = epPtr->wait(this, -1) ;
        }
        if(ret < 0) {
>>>>>>> 7f5767318cdf45305c3acc000c256e83bf9e4903
            quit = true ;
        }
    
        //epoll返回０，没有活跃事件
        else if(ret == 0) {
        }
        else {
            //要是事件集合不为空
            while(!activeChannels.empty()) {
                channel chl = activeChannels.front() ;
                activeChannels.pop() ;
                //处理事件
                //适用线程处理
                //在线程中处理将本conn传进去完成事件的channel的删除操作
                //以及 从Epoll中删除的操作
                //要保证删除或修改的原子性
                //现将函数转化成函数指针
                //处理完就弹出队列
                auto f = std::bind(&eventLoop::commitEvent, this, chl) ;
                //将函数传进去
                pool->commit(f);
//                int n = chl.handleEvent() ;
                //将已经关闭的连接，收集起来
              /*  if(n == 0) {
                    closeList.push_back(chl) ;
                }*/
            }
        /*
            //清除掉所有关闭事件
            int s = closeList.size() ;
            //从clList将关闭事件清除
            if(s != 0) {
                int n = clearCloseChannel(closeList) ;
                if(n < 0) {
                    std :: cout << __FILE__<< "    " << __LINE__<< std::endl ;
                }
            }
            //清空活跃事件集合
            activeChannels.clear() ;
<<<<<<< HEAD
        }
    } */  
}
/*
void eventLoop::loop() {
    int quit = true ;
    int fd = chl.getFd() ;
    while(quit) {
        int ret = ep.poll() ;
           
    }
}
*/
=======
        */}

    }   
}

//对于connection的修改要保证原子性:
int eventLoop :: commitEvent( channel chl) {

    std::unique_lock<std::mutex>lock(*conn->getMutex()) ;
    //处理活跃的事件,处理相应的事件不加锁
    int n = chl.handleEvent() ;
    //返回0，将事件从列表中删除掉，删除步骤：先从Epoll中一处事件
    //在从cliList移除事件
    if(n == 0) {
        int ret = clearCloseChannel(chl) ;
        if(ret < 0) {
            std::cout << __FILE__ << "        " << __LINE__ << std::endl ;
        }
        return -1 ;
    }
    return 1 ;
}

>>>>>>> 7f5767318cdf45305c3acc000c256e83bf9e4903
//将活跃的事件加入到活跃事件表中
int eventLoop :: fillChannelList(channel* chl) {
   activeChannels.push(*chl) ;
   return 1 ;
}

//值有监听套接字拥有connection
//向loop中添加新的conn.将这个连接加入到epoll中
void eventLoop :: addConnection(connection* con) {
    
    conn = con ;
    //获取到线程池
    pool = con->getPool() ;
    std::shared_ptr<channel> channel_ = conn->getChannel() ;
    int fd = channel_->getFd() ;
    servFd = fd ;
    channel_->setEpFd(epPtr->getEpFd()) ;
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

//接收连接并添加channel，新建channel
channel eventLoop :: handleAccept() {
    channel tmp;
    tmp.setSock(conn->getSock()) ;
    //创建新连接
    int conFd = tmp.handleAccept(servFd) ;
    tmp.setFd(conFd) ;
    //为channel设置回调
    //设置套接字非阻塞
    conn->setnoBlocking(conFd) ;
    tmp.setEpFd(epPtr->getEpFd()) ;
    //设置可读和描述符的原子性
    epPtr->add(conFd, READ|ATOMIC) ;
    conn->setCallBackToChannel(&tmp) ;
    return tmp ;
    //将channel加入到当前loop的列表中
   // clList[conFd] = tmp ;
}
