#pragma once
#include <iostream>
#include <memory>
#include <map>
#include <functional>
#include "Socket.h"
#include "Buffer.h"
#include "EventLoop.h"
#include "Channel.h"
#include "ThreadPool.h"

class channel ;
//封装TCP连接
class connection :
    public std::enable_shared_from_this<connection> {
public:
    connection() ;
    connection(std::string ip, std::string port) ;
    ~connection() ;
public :
    //将套接字类和channel进行绑定
    typedef std :: function<void(channel* chl)> callBack ;
public :
    void setPool(threadPool*p) { this->pool = p ; }
    void createListenFd(socketFd* sock) ;
    void createChannel() {channel_ = std :: make_shared<channel>() ;}
    void createSock() { sock = std::make_shared<socketFd>(); }
    void setConf(std::string ip, std::string port) ;
    std::shared_ptr<socketFd> getSock() { return sock ; }
    void setnoBlocking(int fd_) {sock->setNoBlocking(fd_) ;}
    void setCallBackToChannel(channel* channel_) ;
    //设置channel的各种回调函数
    void setWriteCallBack(callBack cb) ;
    void setCloseCallBack(callBack cb) ;
    void setReadCallBack(callBack cb) ;
    void setTimeoutCallBack(callBack cb) ;
    threadPool* getPool() { return pool ; }
public :
    //创建监听套接字
    //创建指定端口号的监听套接字
    threadPool * pool ;
    int createListenFd(int port) ;
    //创建指定IP和端口号的监听套接字
    //监听套接字接收新连接
    int doAccept() ;
    //发送消息
    void sendMessage(Buffer*buffer) ;
    //关闭连接，实则是关闭套接字的写端
    //套接字真正的关闭时期是其对应的connection消亡
    void shutdown() ;
    std::shared_ptr<channel>  getChannel() {
        return (this->channel_) ;
    }
    void setMutex(std::mutex* mute) { this->mute = mute ; }
    std::mutex* getMutex() { return mute ;}
private :
    //三种回调
    callBack readCallBack ;
    callBack writeCallBack ;
    callBack closeCallBack ;
    callBack timeoutCallBack ;
    //属于本套接字的buffer
    Buffer buffer ;
    std::shared_ptr<channel>channel_ ;
    //socketFd和事件处理器channel绑定
    //封装监听套接字或者连接套接字类和channel对象的类
    //监听套接字
    std::shared_ptr<socketFd> sock ;
    std::mutex * mute ;
    //该连接的套接字
    int fd = -1;
} ;

