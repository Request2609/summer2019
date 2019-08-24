#pragma  once
#include <memory>
#include <atomic>
#include <iostream>
#include <queue> 
#include <thread>
#include <mutex> 
#include <map>
#include "Channel.h"
#include "Epoll.h"
#include "Connection.h"
#include "acceptor.h"

class channel ;
class connection ;
class epOperation ;

class loopInfo {
public :
    loopInfo() { 
        ep = make_shared<epOperation>() ;
    }
    ~loopInfo() { close(ep->getEpFd()) ;}
public :
    void add(channel*chl) { chlList.insert(make_pair(chl->getFd(), chl)) ; }
    channel* getChl() { return &chl ; }
    int addConnect(channel* chl) ;
    void wakeCb(channel* chl); 
    int setChannel() ;
    channel* search(int fd) ;
    shared_ptr<epOperation> getEp() { return ep ; }
    int buildWakeFd() ; 
    //返回所属线程唤醒句柄
    int getWriteFd() { return wakeupFd[0]; }
    //唤醒读事件
    int getReadFd() { return wakeupFd[1] ; }
    //返回所属线程epoll句柄
    int getEpFd() { return ep->getEpFd() ; }
    //返回线程id
    int delChl(int fd) ;
    void setThreadId(long id) { threadId = id ; }
private :
    channel chl ;
    //事件循环中的epoll
    shared_ptr<epOperation>ep ;
    //唤醒线程的fd
    int wakeupFd[2] ;
    //线程id
    long threadId ; 
    //该loop管理的事件集合
    map<int, channel*>chlList ;
} ;

//事件循环 EventLoop和connection共享channel对象
class eventLoop {   
    typedef std::map<int, channel> channelMap;
public:
    eventLoop() ;
    ~eventLoop() {}
public :
    int wakeup(int fd) ;
    int doPendingFunc(channel* chl) ;
    void runThread() ;
    channel* search(int fd) ;
    int getListenFd() { return servFd ; }
    void loop() ;
    void addConnection(connection* con) ;
    void addClList(int fd, channel& channel_) ;
    int fillChannelList(channel*chl) ;
    channel  handleAccept() ;
    int clearCloseChannel(std::vector<channel>&list_) ;
    void round(loopInfo& loop) ;
    int queueInLoop(channel& chl, int& num) ;
public :
    static int getNum() ;
private :
    static int threadNum ;
    mutex mute ;
    //线程
    vector<thread> threads ;
    //线程loop中的重要信息
    vector<loopInfo> info ;
    int servFd  = -1 ;
    connection* conn ;
    //reactor in thread
    //一个eventLoop一个epoll
    std :: shared_ptr<epOperation> epPtr ;
    //活跃事件列表
    std :: vector<channel> activeChannels;
    map<loopInfo*, channel*> qChl ;
    //该eventLoop对应的监听套接字封装
    //退出标志
    bool quit ;
    //设置套接字channel键值对
    channelMap clList ;
};

