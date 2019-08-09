#pragma  once
#include <memory>
#include <atomic>
#include <iostream>
#include <functional>
#include <mutex>
#include <thread>
#include <map>
#include "Channel.h"
#include "ThreadPool.h"
#include "Epoll.h"
#include "Connection.h"

class channel ;
class connection ;
class epOperation ;
//事件循环 EventLoop和connection共享channel对象
class eventLoop
{   
    typedef std::map<int, channel> channelMap;
public:
    eventLoop() ;
    ~eventLoop() {}
public :
    channel* search(int fd) ;
    int getListenFd() { return servFd ; }
    void loop() ;
    void addConnection(connection* con) ;
    void addClList(int fd, channel& channel_) ;
    int fillChannelList(channel*chl) ;
<<<<<<< HEAD
    channel handleAccept() ;
    int clearCloseChannel(std::vector<channel>&list_) ;
    void loop(epOperation ep, channel chl) ; 
=======
    void handleAccept() ;
    void setPool(threadPool* pl) { this->pool = pl ; }
    int clearCloseChannel(std::vector<channel>&list_) ;
    int clearCloseChannel(channel chl) ;
    int commitEvent(channel chl) ;
>>>>>>> 7f5767318cdf45305c3acc000c256e83bf9e4903
private:
    threadPool* pool ;
    int servFd  = -1 ;
    connection* conn ;
    //reactor in thread
    //一个eventLoop一个epoll
    std :: shared_ptr<epOperation> epPtr ;
    //活跃事件列表
    //多个线程共享资源
    std :: queue<channel> activeChannels;
    //该eventLoop对应的监听套接字封装
    //退出标志
    bool quit ;
    //设置套接字channel键值对
    channelMap clList ;
};

