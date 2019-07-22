#include <iostream>
#include<muduo/net/TcpConnection.h>
#include<muduo/net/EventLoop.h>
#include<muduo/net/TcpServer.h>
#include<muduo/net/InetAddress.h>
using namespace std ;

void onConnection(const muduo::net::TcpConnectionPtr& conn) {
    if(conn->connected()) {
        conn->shutdown() ;
    } 
}
int main()
{
    muduo::net::EventLoop loop ;
    muduo::net::TcpServer server(&loop, muduo::net::InetAddress(8899), "Finger") ;
    server.setConnectionCallback(onConnection) ;
    server.start() ;
    loop.loop() ;
    return 0;
}

