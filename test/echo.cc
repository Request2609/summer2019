#include"echo.h"


int main()
{
    muduo::net::EventLoop loop ;
    
    echoServer echoServer(&loop, muduo::net::InetAddress(2098)) ;
    echoServer.start() ;
    loop.loop() ;
    return 0;
}

