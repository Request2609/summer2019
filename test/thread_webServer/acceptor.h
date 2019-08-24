#pragma once
#include <memory>
#include "Channel.h"
#include "Epoll.h"
using namespace std ;

class acceptor {
public:
    //创建channel对象
    acceptor() {
       chl = make_shared<channel>() ;
    }
    ~acceptor() {}

public :
    long getThreadNum() { return threadNum ; }
    void setThreadNum(long num) { threadNum = num ; }
    shared_ptr<channel> getChl() { return chl ; }
    shared_ptr<epOperation> setEpHandle(shared_ptr<epOperation>ep) { this->ep = ep  ;}
private:
    int threadNum ;
    shared_ptr<channel>chl ;
    int epFd ;
    shared_ptr<epOperation> ep ;
};

