#include <iostream>
#include<thread>
#include<muduo/net/TcpConnection.h>
#include<muduo/net/EventLoop.h>
#include<muduo/net/TcpServer.h>
#include<muduo/net/InetAddress.h>
using namespace std ;


void threadFunc() {
    cout << "threadFunc():pid=" << getpid() << "当前线程ID:" << muduo::CurrentThread::tid() << endl ;
    muduo::net::EventLoop loop ;
    loop.loop() ;
}

int main()
{   
    muduo::net::EventLoop loop ;
    thread t(threadFunc) ;
    t.join() ;
    return 0;
}

