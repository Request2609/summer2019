#pragma once
#include <iostream>
#include<muduo/net/TcpConnection.h>
#include<muduo/net/EventLoop.h>
#include<muduo/net/TcpServer.h>
#include<muduo/net/InetAddress.h>
using namespace std ;

using std:: placeholders:: _1 ;
using std:: placeholders:: _2 ;
using std:: placeholders:: _3 ;

class echoServer
{
public:
    echoServer(muduo::net::EventLoop* loop, const muduo::net::InetAddress& listenAddr) ;
    void start() ;
private:
    void onConnection(const muduo::net::TcpConnectionPtr&conn) ;
    void onMessage(const muduo::net::TcpConnectionPtr&conn, 
                   muduo::net::Buffer*buf, 
                   muduo::Timestamp time) ;
    muduo::net::TcpServer server ;
};

//给类成员必须初始化
echoServer::echoServer(muduo::net::EventLoop* loop, 
                       const muduo::net::InetAddress& listenAddr) 
    :server(loop, listenAddr, "EchoServer") {
    //TcpServer初始注册各种回调函数
    server.setConnectionCallback(std::bind(&echoServer::onConnection, this, _1)) ;
    server.setMessageCallback(std::bind(&echoServer::onMessage, this, _1, _2, _3)) ;
}

void echoServer::onMessage(const muduo::net::TcpConnectionPtr&conn, 
                           muduo::net::Buffer*buf, 
                           muduo::Timestamp time) {
    muduo::string msg(buf->retrieveAllAsString())  ;
    conn->send(msg) ;
}


void echoServer::onConnection(const muduo::net::TcpConnectionPtr&conn) {
}

void echoServer::start() {
    server.start() ;
}
