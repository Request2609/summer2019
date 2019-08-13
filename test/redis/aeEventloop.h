#pragma once
#include <functional>
#include <map>
#include <memory> 
#include "aeEpoll.h"
#include "aeEvent.h"

#define SIZE 1024
using namespace std ;


//创建事件循环
class aeEventloop {
    typedef function<void()> callBack ;
public :
    shared_ptr<aeEpoll> aep ;
    //最大文件描述符的值，感觉在epoll中也没什么用
    int maxFd ;
    //文件描述符的个数
    int setSize ;   
    //下一个时间事件ID标识
    long long timeEventNextId ;
    //设置事件
    map<int, shared_ptr<aeEvent>> eventData ;
    //停止标志
    int stop ;
    //处理底层API的数据
    void* apiData ;
    //触发的事件列表
    vector<epoll_event>fireList ;
private :
    aeEventloop() ; 
    ~aeEventloop() ;
public :
    void setCallBack(callBack readCb, callBack writeCb) ;
    int addServerEvent(string port, string addr) ;
    int start() ;
} ;

