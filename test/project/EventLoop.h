#pragma once
#include <atomic>
#include <iostream>
#include "Connection.h"
//事件循环
class eventLoop
{
public:
    eventLoop() ;
    ~eventLoop() {}
public :
    void loop() ;
    void qiut() ;
private:
    //该eventLoop对应的监听套接字封装
    connection conn ; 
    //退出标志
  //  int threadNum ;
    std :: atomic<bool> quit ;
   // std::unique_ptr<threadPool> pool ;
};

