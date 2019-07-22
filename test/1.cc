#include <iostream>
#include<muduo/net/TcpConnection.h>
#include<muduo/net/EventLoop.h>
#include<muduo/net/TcpServer.h>
#include<muduo/net/InetAddress.h>
using namespace std ;
void  onMessage(const muduo::net::TcpConnectionPtr&conn, muduo::net::Buffer* buf, muduo :: Timestamp time) {
    
    const char* crlf = buf->findCRLF() ;
    if(crlf) {
        string user(buf->peek(), crlf) ;
        cout << user << endl ;
        conn->send(user+"\r\n") ;
    }
}
int main()
{
    //设置事件循环
    muduo::net::EventLoop loop ;
    muduo::net::TcpServer server(&loop, muduo::net::InetAddress(1097), "hello muduo") ;
    server.setMessageCallback(onMessage) ;
    server.start() ;
    loop.loop() ;
    return 0;
}

