#include <iostream>
#include<functional>
#include "TcpServer.h"
#include "EventLoop.h"
#include "Channel.h"
using namespace std ;

void onRead(channel* chl) {
    Buffer* bf =chl->getReadBuffer() ;
    //解析请求行
    int readIndex = bf->getReadIndex() ;
    int writeIndex = bf->getWriteIndex() ;
    string a = bf->readBuffer(readIndex, writeIndex) ;
    //将信息获取完成，再解析
    //解析请求行
    int contentLength = 0 ;
    string end ="";
    while(end != "\r\n\r\n") {
                 
    }
}

int main(int argc, char** argv) {
    eventLoop loop ;
    tcpServer server(&loop, argv[1]) ;
    connection conn ;
    //设置新连接的回调函数
    conn.setReadCallBack(std::bind(onRead, placeholders::_1)) ;
    //将新建的连接加入到loop中
    server.addNewConnection(conn) ;
    //服务器开始工作
    server.start() ;
    //开始等待事件
    loop.loop() ;
    return 0;
}

