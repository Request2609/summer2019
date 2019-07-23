#include <iostream>
#include<sys/timerfd.h>
#include<muduo/net/TcpConnection.h>
#include<muduo/net/EventLoop.h>
#include<muduo/net/TcpServer.h>
#include<muduo/net/InetAddress.h>
using namespace std ;

muduo::net::EventLoop* g_loop ;
void timeout() {
    cout << "Timeout\n" << endl ;
    g_loop->quit() ;
}

int main()
{
    muduo::net::EventLoop loop ;
    g_loop = &loop ;
    int timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK|TFD_CLOEXEC) ;
    muduo::net::Channel cc(&loop, timerfd) ;
    cc.setReadCallBack(timeout) ;
    hannel.enableReading() ;
    struct itimerspec howlong ;
    bzero(&howlong, sizeof(howlong)) ;
    howlong.it_value.tv_sec = 5 ;
    ::timerfd_settime(timerfd, 0, &howlong, NULL) ;
    loop.loop() ;
    ::close(timerfd) ;
    return 0;
}

