#pragma once
#include <functional>
#include <fcntl.h>
#include <mutex>
#include <queue>
#include "ThreadPool.h"
#include "Epoll.h"
#include "UnixSock.h"
#include "Channel.h"
#include "Buffer.h"

class epOperation ;
class channel ;
//post登录的数据包
struct logBuf {
    //服务类型
    int flag = 0;
    int type ;
    //用户名
    char name[512] ;
    //密码
    char password[512] ;
    char version[1024] ;
    char path_[1024] ;
} ;

class process {
    typedef std::function<void(channel chl)> callBack ;
public :
    process(int num):pool(num) {}
    ~process() {}
public :
    void createEpoll() { ep=std::shared_ptr<epOperation>(new epOperation()) ;}
    int handleRead(channel* chl) ;
    int handleWrite(channel& chl) ;
    void start() ;
    int handleAccept() ;
    void append(struct epoll_event& ev) ;
    void setReadCallBack(callBack cb) { readCall = std::move(cb) ; }
    void setWriteCallBack(callBack cb) { writeCall = std::move(cb) ; }
    int bindListen() ;
    int getFd() { return uSock.getFd() ; }
    int setNoBlocking(int fd) ;
    int addEpoll(int fd, int event) ;
private :
    std::mutex mtx ;
    logBuf buf ;   
    threadPool pool ;
    callBack readCall ;
    callBack writeCall ;
    std::shared_ptr<epOperation> ep ;
    uSocketFd uSock ;
    //活跃事件列表
    std::queue<channel> activeEvent ;
} ;

