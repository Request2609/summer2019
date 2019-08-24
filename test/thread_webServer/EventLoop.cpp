#include"EventLoop.h" 

eventLoop :: eventLoop() {
    //开8线程
    threadNum = 8 ;
    //创建一个epoll
    epPtr = std::make_shared<epOperation>() ;
    quit = false ;
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

//创建双向管道，用来唤醒事件分离器
int loopInfo :: buildWakeFd() { 
    int ret = socketpair(AF_UNIX, SOCK_STREAM, 0, wakeupFd) ;
    if(ret < 0) {
        cout << __FILE__ << "           " <<__LINE__ << endl ;
        return ret ;
    }
    return 1 ;
}

//创建线程
void eventLoop :: runThread() {
    //开辟线程,创建epoll
    for(int i=0; i<threadNum; i++) {
    //    threads.push_back(round) ;
        thread t ;
        threads.push_back(t) ;
    }
    ///让线程跑起来
    for(int i=0; i<threadNum; i++) {
        loopInfo infos ;
        infos.buildWakeFd() ;
        infos.setChannel() ;
        info.push_back(infos) ;
        threads[i] = thread(&eventLoop::round, ref(infos)) ;  
    }
}

//唤醒某个线程
int eventLoop :: wakeup(int fd) {
    int ret = 1 ;
    int res = send(fd, &ret, sizeof(ret), 0) ;
    if(res < 0) {
        cout << __FILE__ << "         " << __LINE__ << endl ;
        return -1 ;
    }
    return 1 ;
}

//为唤醒描述符设置channel
int loopInfo :: setChannel() {
    int fd = wakeupFd[1] ;
    chl.setFd(fd) ;
    chl.setEvents(READ) ;
    int epFd = ep->getEpFd() ;
    chl.setEpFd(epFd) ;
    ep->add(epFd, fd) ;
    auto func = bind(&loopInfo::wakeCb, this,  placeholders::_1) ;
    //设置读回调
    connection tmp ;
    tmp.setReadCallBack(func) ;
    tmp.setCallBackToChannel(&chl) ;
   // chl.setReadCallBack(func) ;
    return 1 ;
}

//唤醒函数，将唤醒套接字缓冲区中的数据读出来,不关闭套接字
void loopInfo :: wakeCb(channel* chl) {
    int fd = chl->getFd() ;
    int ret  = 0 ;
    int res= read(fd, &ret, sizeof(ret)) ;
    if(res < 0) {
        cout << __FILE__ << "         " << __LINE__ << endl ;   
        return  ;
    }
}

channel* loopInfo :: search(int fd) { 
    if(chlList.find(fd) == chlList.end()) {
        return NULL ;
    }
    return chlList[fd] ;
}

//绑定匿名unix套接字
void eventLoop :: round(loopInfo& loop) {

    int wakeFd = loop.getReadFd() ;
    int stop = 0 ;
    //获取epoll
    shared_ptr<epOperation>ep = loop.getEp() ;
    channel* chl = loop.getChl() ;
    //将当前唤醒的channel加入到list中
    loop.add(chl) ;
    while(!stop) {
        vector<channel>actChl ;
        vector<channel>closeChannel ;
        int ret = ep->roundWait(loop, actChl) ;    
        if(ret < 0) {
            stop = true  ;
        }
        //处理事件
        for(channel chl : actChl) {
            int fd = chl.getFd() ;
            //该从队列中取连接了
            if(fd == wakeFd) {
                doPendingFunc(&chl) ;
                continue ;
            }
            int res = chl.handleEvent() ;
            if(res == 0) {
                closeChannel.push_back(chl) ;
            }
        }
        //处理完就删除
        actChl.clear() ;
        //清理map中的channel 
        for(channel chl : closeChannel) {
            loop.delChl(chl.getFd()) ;
            //从epolｌ中移除
            ep->del(chl.getFd()) ;
        }
        closeChannel.clear() ;
    }
}

int eventLoop :: doPendingFunc(channel* chl) {

    //从队列中取东西
    mute.lock() ;
       
    mute.unlock() ;
}

int loopInfo :: delChl(int fd) {
    map<int, channel*>::iterator iter = chlList.find(fd) ;
    if(iter != chlList.end()) {
        return -1 ;
    }
    //删除fd对应的事件
    chlList.erase(iter) ;
} 

int eventLoop:: getNum() {
    static int num = -1 ;
    num++ ;
    if(num == eventLoop::threadNum) {
        num = 0 ;
    }
    return num ;
}

void eventLoop :: loop() {
    runThread() ;
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
        }
        //将事件分发给各个线程
        else {
           // std::vector<channel>closeList ;a
            //处理连接，所有连接事件分给各个线程中的reactor
            for(channel chl : activeChannels) {
                //获取一个编号
                int num = getNum() ; 
                queueInLoop(chl, num) ;
              //  qChl.push(&chl) ;
                //绑定channel和相应的loopInfo
                //处理事件
             //   int n = channel.handleEvent() ;
                //将已经关闭的连接，收集起来
              //  if(n == 0) {
            //        closeList.push_back(channel) ;
               // }
            }
            //int s = closeList.size() ;
            //从clList将关闭事件清除
          /*  if(s != 0) {
                int n = clearCloseChannel(closeList) ;
                if(n < 0) {
                    std :: cout << __FILE__<< "    " << __LINE__<< std::endl ;
                }
            }*/
            //清空活跃事件集合
            activeChannels.clear() ;
        }
    }   
}

//往队列中加数据
int eventLoop :: queueInLoop(channel& chl, int& num) {
    mute.lock(); 
    //向队列中插入元素
    qChl.insert(make_pair(&info[num], &chl)) ;
    //通知线程接收新连接
    wakeup(info[num].getWriteFd()) ;
    mute.unlock() ;
}   

//将活跃的事件加入到活跃事件表中
int eventLoop :: fillChannelList(channel* chl) {
   activeChannels.push_back(*chl) ;
   return 1 ;
}

//值有监听套接字拥有connection
//向loop中添加新的conn.将这个连接加入到epoll中
void eventLoop :: addConnection(connection* con) {
    
    conn = con ;
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

//接收连接并添加channel
channel eventLoop :: handleAccept() {
    channel tmp;
    tmp.setSock(conn->getSock()) ;
    //创建新连接
    int conFd = tmp.handleAccept(servFd) ;
    tmp.setFd(conFd) ;
    //为channel设置回调
    //设置套接字非阻塞
    conn->setnoBlocking(conFd) ;
  //  tmp.setEpFd(epPtr->getEpFd()) ;
    //设置监听事件类型
    tmp.setEvents(READ) ;
   // epPtr->add(conFd, READ) ;
    //给channel设置回调函数
    conn->setCallBackToChannel(&tmp) ;   
    //将channel加入到当前loop的列表中
//    clList[conFd] = tmp ;
    return tmp ;
}
