#pragma once
#include <functional>
#include <memory> 
#include "channel.h"

using namespace std ;
//创建文件事件
class aeFileEvent {
    //创建文件描述符
    typedef function<void()> callBack ;
private :
    //标志位,表示事件结构体是否在被使用
    int mask ;
    //读回调函数
    callBack readFunc ;
    //写回调函数
    callBack writeFunc ;
    //客户端的数据
    shared_ptr<channel>clientData ;
public :
     
} ;
class aeEventLoop {
public :
    //最大文件描述符的值，感觉在epoll中也没什么用
    int maxFd ;
    //文件描述符的个数
    int setSize ;   
    //下一个时间事件ID标识
    long long timeEventNextId ;
    //监测系统时间
    shared_ptr<aeFileEvent> event ;
    //停止标志
    int stop ;
    //处理底层API的数据
    void* apidata ;
private :
} ;

class aeEvent{
private :
    aeEvent() {}
    ~aeEvent() {} 
public :

} ;
