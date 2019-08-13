#pragma once
#include <memory>
#include <functional>
#include <map>
#include "aeSocket.h"
#include "buffer.h"
#include "aeSocket.h"
using namespace std ;
//创建连接事件信息
class aeEvent {
    //创建文件描述符
    typedef function<void()> callBack ;
public :
    aeEvent() {
    }
    ~aeEvent() {
    }
private :
    //套接字对象
    aeSocket sock ;
    //标志位,表示事件结构体是否在被使用
    int mask ;
    //用户缓冲区
    buffer buf ;
    //读回调函数
    callBack readFunc ;
    //写回调函数
    callBack writeFunc ;
public :
    aeSocket* getSocket() {
        return &sock ;
    }
    buffer* getBuf() { return &buf ; }
    void setReadCallBack(callBack cb) { readFunc = cb ;}
    void setWriteCallBack(callBack cb) { writeFunc = cb; }
} ;

