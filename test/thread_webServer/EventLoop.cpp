#include"EventLoop.h" 
#include "Call.h"

eventLoop :: eventLoop() {
    //开8线程
    //创建一个epoll
    threadNums = 8 ;
    epPtr = std::make_shared<epOperation>() ;
    quit = false ;
    pool = make_shared<threadPool>(8);
}

eventLoop:: ~eventLoop() {
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
    
    
    for(int i=0; i<threadNums; i++) {
        loopInfo infos ;
        infos.buildWakeFd() ;
        infos.setChannel() ;
        info.push_back(infos) ;
        auto func = bind(&eventLoop::round, this, placeholders::_1) ;
        pool->commit(func, ref(infos)) ;
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

    chl = make_shared<channel>() ;
    int fd = wakeupFd[1] ;
    //设置非阻塞
    //setNoBlock(fd) ;
    chl->setFd(fd) ;
    chl->setEvents(READ) ;
    int epFd = ep->getEpFd() ;
    //为唤醒套接字设置epoll
    chl->setEpFd(epFd) ;
    //现在不能添加到epoll中!!!
    ep->add(fd, READ) ;
    //设置读回调
    connection tmp ;
    tmp.setWakeChlCall(chl) ;
    return 1 ;
}

int loopInfo :: setNoBlock(int fd) {
    int ret = fcntl(fd, F_GETFL) ;
    ret |= O_NONBLOCK ;
    ret = fcntl(fd, F_SETFL, ret) ;
    return ret ;
}

void loopInfo :: wakeCb(channel* chl) {
    int fd = chl->getFd() ;
    int ret  = 0 ;
    int res= read(fd, &ret, sizeof(ret)) ;
    if(res < 0) {
        cout << __FILE__ << "         " << __LINE__ << endl ;   
        return  ;
    }
}


shared_ptr<channel> loopInfo :: search(int fd) { 
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
    shared_ptr<channel>chl = loop.getChl() ;
    //将当前唤醒的channel加入到list中
    loop.add(chl->getFd(), chl) ;
    //将wakeFd加入到epoll中
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

//唤醒线程
int eventLoop :: doPendingFunc(channel* chl) {
    if(qChl.empty()) { 
        return -1 ;
    }
    chl->handleEvent() ;
    vector<pair<loopInfo*, channel*>>ls ;
    int wFd = chl->getFd() ; 
    //从队列中取东西
    {
        lock_guard<mutex>lk(mute) ;
        for(pair<loopInfo*, channel*>p : qChl) {
            //当唤醒的fd与channel对应的fd相等的时候
            if(p.first->getReadFd() == wFd) {
                ls.push_back(p) ;
            }
        }
        //从qChl中清除掉
        for(pair<loopInfo*, channel*>p : ls) {
            qChl.erase(qChl.find(p.first)) ;
        }
    }

    //将新连接加入到epoll中,操作局部变量线程安全
    for(pair<loopInfo*, channel*>p:ls) {
        shared_ptr<epOperation>ep = p.first->getEp() ;
        p.second->setEpFd(ep->getEpFd()) ;
        //设置可读事件并加入到epoll中
        ep->add(p.second->getFd(), READ) ;
        p.first->add(p.second->getFd(), shared_ptr<channel>(p.second)) ;
    }
    return 1 ;
}

int loopInfo :: delChl(int fd) {
    map<int, shared_ptr<channel>>::iterator iter = chlList.find(fd) ;
    if(iter != chlList.end()) {
        return -1 ;
    }
    //删除fd对应的事件
    chlList.erase(iter) ;
    return 1 ;
} 

int eventLoop:: getNum() {
    static int num = -1 ;
    num++ ;
    if(num == threadNums) {
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
            //处理连接，所有连接事件分给各个线程中的reactor
            for(channel chl : activeChannels) {
                //获取一个编号
                int num = getNum() ; 
                queueInLoop(chl, num) ;
            }
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
    mute.unlock() ;
    wakeup(info[num].getWriteFd()) ;
    return 1 ;
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
    //设置监听事件类型
    tmp.setEvents(READ) ;
    //给channel设置回调函数
    conn->setCallBackToChannel(&tmp) ;   
    //将channel加入到当前loop的列表中
    return tmp ;
}
