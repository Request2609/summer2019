#pragma once
#include <functional>
#include <map>
#include "redisDb.h"
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
    //数据库数组
    vector<shared_ptr<redisDb>>db ;
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
    //db服务器的保存的条件
    //像定时条件等
    map<string, long>param ;
    //记录距离上一次save，服务器修改了多少次数据库状态
    long dirty ;
    //现在距离上一次执行save命令的时间
    long lastsave ;

private :
    aeEventloop() ; 
    ~aeEventloop() ;
public :
    void setCallBack(callBack readCb, callBack writeCb) ;
    int addServerEvent(string port, string addr) ;
    int start() ;
} ;

